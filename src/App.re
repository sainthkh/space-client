let styles: AppStyles.definition = [%raw {| require("./App.scss") |}]

type state = {
  page: Url.page,
};

type action = ChangePage(Url.page);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {
    page: Index,
  },

  didMount: self => {
    let watchID = ReasonReact.Router.watchUrl(url => {
      switch(url.path) {
      | [""] => self.send(ChangePage(Index))
      | _ => self.send(ChangePage(Error404))
      }
    })
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watchID));
  },

  reducer: (action: action, _state: state) => {
    switch(action) {
    | ChangePage(page) => ReasonReact.Update({ page: page })
    }
  },

  render: _self => {
    let launch: Types.launch = {
      id: 1,
      site: "Hello, world",
      mission: {
        name: "HI",
        missionPatch: "big",
      },
      rocket: {
        id: 3,
        name: "Good",
        type_: "Awesome",
      },
      isBooked: false,
      backgroundImage: None,
    };

    <div>
      <Header />
      <LaunchTile launch />
      <button className="btn">{ ReasonReact.string("Load more") }</button>
      <Loading />
    </div>
  }
}
