module GetLaunchDetails = [%graphql {|
  query LaunchDetails($launchId: ID!) {
    launch(id: $launchId) {
      id
      site
      isBooked
      rocket {
        name
        type
      }
      mission {
        name
        missionPatch
      }
    }
  }
|}]

module GetLaunchDetailsQuery = ReasonApollo.CreateQuery(GetLaunchDetails);

let component = ReasonReact.statelessComponent("LaunchPage")

let make = (
  ~launchId: int,
  _children
) => {
  ...component,

  render: _self => {
    let query = GetLaunchDetails.make(~launchId=string_of_int(launchId), ());
    <GetLaunchDetailsQuery variables=query##variables>
      ...{
        ({result}) => {
          switch(result) {
          | Loading => <Loading />
          | Error(_error) => <p>{ ReasonReact.string("Error") }</p>
          | Data(response) => {
            <p>{ ReasonReact.string("OK") }</p>
          }
          }
        }
      }
    </GetLaunchDetailsQuery>
  }
}
