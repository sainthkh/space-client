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
      | ["launch", id] => self.send(ChangePage(Launch(id)))
      | ["profile"] => self.send(ChangePage(Profile))
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

  render: self => {
    <div>
      <div className=styles##bar></div>
      <div className=styles##container>
        {switch(self.state.page){
        | Index => <LaunchesPage />
        | Launch(launchId) => <LaunchPage launchId=int_of_string(launchId) />
        | Profile => <ProfilePage />
        | Error404 => <LaunchesPage /> /* temporary */
        }}
      </div>
      <Footer />
    </div>
  }
}
