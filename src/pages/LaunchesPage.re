module GetLaunches = [%graphql {|
  query getLaunchList($after: String) {
    launches(after: $after) {
      cursor
      hasMore
      launches {
        id
        rocket {
          name
        }
        mission {
          name
        }
      }
    }
  }
|}]

module GetLaunchesQuery = ReasonApollo.CreateQuery(GetLaunches);

let component = ReasonReact.statelessComponent("LaunchesPage")

let make = (_children) => {
  ...component,

  render: _self => {
    <GetLaunchesQuery>
      ...{
        (({result, fetchMore}) => {
          switch(result) {
          | Loading => <Loading />
          | Error(_error) => <p>{ ReasonReact.string("Error") }</p>
          | Data(response) => 
            <>
              <Header />
              {
                response##launches##launches
                |> Js.Array.mapi((launch, i) => {
                  <LaunchTile
                    key=string_of_int(i)
                    launchID=int_of_string(launch##id)
                    missionName=launch##mission##name
                    rocketName=launch##rocket##name
                    backgroundUrl=None
                  />
                })
                |> ReasonReact.array
              }
              
            </>
          }
        })
      }
    </GetLaunchesQuery>
  }
};
