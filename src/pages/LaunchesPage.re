type nameOnly = {
  name: string,
}

type launch = {
  id: int,
  rocket: nameOnly,
  mission: nameOnly,
};

type launches = {
  __typename: string,
  cursor: string,
  hasMore: bool,
  launches: array(launch),
};

module GetLaunches = [%graphql {|
  query getLaunchList($after: String) {
    launches(after: $after) @bsRecord {
      __typename
      cursor
      hasMore
      launches @bsRecord {
        id @bsDecoder(fn: "int_of_string")
        rocket @bsRecord {
          name
        }
        mission @bsRecord {
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
          | Data(response) => {
            let response = response##launches;
            <>
              <Header />
              {
                response.launches
                |> Js.Array.mapi((launch, i) => {
                  <LaunchTile
                    key=string_of_int(i)
                    launchId=launch.id
                    missionName=launch.mission.name
                    rocketName=launch.rocket.name
                    backgroundUrl=None
                  />
                })
                |> ReasonReact.array
              }
              {
                switch(response.hasMore) {
                | false => { ReasonReact.string("") }
                | true =>
                  <button 
                    className="btn"
                    onClick={_ => {
                      open Js;
                      open Js.Dict;

                      let variables = Dict.empty();
                      variables->set("cursor", response.cursor->Json.string)
                      
                      fetchMore(
                        ~variables=variables->Json.object_,
                        ~updateQuery=(prev, next) => {
                          switch(next->ReasonApolloQuery.fetchMoreResultGet) {
                          | None => prev
                          | Some(next) => {
                            open Jsonx;
                            
                            let result = obj(next);
                            let prev = obj(prev)->emptyIfNone("launches");
                            let launches = result->emptyIfNone("launches");
                            launches->set("launches", 
                              concat(
                                prev->defaultIfNone("launches", Json.array([||])), 
                                launches->defaultIfNone("launches", Json.array([||]))
                              )
                            )
                            
                            result->set("launches", launches->Json.object_);
                            result->Json.object_;
                          };
                          }
                        },
                        ()
                      )
                      |> ignore
                    }}
                    >
                    { ReasonReact.string("Load More") }
                  </button>
                }
              }
            </>
          }
          }
        })
      }
    </GetLaunchesQuery>
  }
};
