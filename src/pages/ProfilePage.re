type nameOnly = {
  name: string,
};

type launch = {
  id: int,
  rocket: nameOnly,
  mission: nameOnly,
}

type me = {
  id: int,
  email: string,
  trips: array(launch),
};

module GetMyTrips = [%graphql {|
  query GetMyTrips {
    me @bsRecord {
      id @bsDecoder(fn: "int_of_string")
      email
      trips @bsRecord {
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
|}];

module GetMyTripsQuery = ReasonApollo.CreateQuery(GetMyTrips);

let component = ReasonReact.statelessComponent("Profile");

let make = (_children) => {
  ...component,

  render: _self => {
    <GetMyTripsQuery>
    ...{
      ({result}) => {
        switch(result) {
        | Loading => <Loading />
        | Error(error) => <p>{ ReasonReact.string(error##message) }</p>
        | Data(response) => {
          let me = response##me;

          <>
            <Header title="My Trips" />
            {switch(Array.length(me.trips)){
            | 0 => <p>{ ReasonReact.string("You haven't booked any trips.") }</p>
            | _ => 
              me.trips
              |> Array.map(trip => {
                let { id, mission, rocket } = trip;

                <LaunchTile 
                  key=string_of_int(id)
                  launchId=id
                  missionName=mission.name
                  rocketName=rocket.name
                  backgroundUrl=None
                />
              })
              |> ReasonReact.array
            }}
          </>
        }
        }
      }
    }
    </GetMyTripsQuery>
  }
}
