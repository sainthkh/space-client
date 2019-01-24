type rocket = {
  name: string, 
  type_: string,
}

type mission = {
  name: string,
  missionPatch: string,
}

type launch = {
  id: int,
  site: string,
  isBooked: bool,
  rocket: rocket,
  mission: mission,
};

module GetLaunchDetails = [%graphql {|
  query LaunchDetails($launchId: ID!) {
    launch(id: $launchId) @bsRecord {
      id @bsDecoder(fn: "int_of_string")
      site
      isBooked
      rocket @bsRecord {
        name
        type_
      }
      mission @bsRecord {
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
            let launch = response##launch;

            switch(launch){
            | None => <p>{ ReasonReact.string("Launch Not Found") }</p>
            | Some(launch) => 
              let { mission, rocket, site, isBooked, } = launch;
              <>
                <Header 
                  title=mission.name 
                  image=mission.missionPatch
                />
                <LaunchDetail
                  rocketName=rocket.name
                  rocketType=rocket.type_
                  site=site
                  backgroundUrl=None
                />
                <ActionButton isBooked isInCart=false />
              </>
            }
          }
          }
        }
      }
    </GetLaunchDetailsQuery>
  }
}
