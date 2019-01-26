type state = {
  page: Url.page,
  ignoreLayout: bool,
};

type action = 
  | CheckLocalStorage
  | RedirectToLoginPage
  | ChangePage(Url.page, bool)

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {
    page: Index,
    ignoreLayout: false,
  },

  didMount: self => {
    let watchID = ReasonReact.Router.watchUrl(url => {
      switch(url.path) {
      | [] | [""] | ["/"] => self.send(ChangePage(Index, false))
      | ["login"] => self.send(ChangePage(Login, true))
      | ["launch", id] => self.send(ChangePage(Launch(id), false))
      | ["profile"] => self.send(ChangePage(Profile, false))
      | _ => self.send(ChangePage(Error404, true))
      }
    })
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watchID));

    self.send(CheckLocalStorage);
  },

  reducer: (action: action, _state: state) => {
    open ReasonReact;
    switch(action) {
    | CheckLocalStorage => SideEffects(self => {
      /* 1. Setting up initial store */
      LocalQuery.writeLogin(~client=GqlClient.instance, ~data={ 
        "isLoggedIn": 
          switch(Dom.Storage.( localStorage |> getItem("token"))) {
          | None => false
          | Some(_) => true
          }
      }, ())

      /* 2. Check login. If not, redirect to login */
      let redirectToLoginPage = () => {
        self.send(RedirectToLoginPage);
      }

      switch(LocalQuery.readLogin(~client=GqlClient.instance, ())) {
      | None => redirectToLoginPage()
      | exception Js.Exn.Error(_e) => redirectToLoginPage()
      | Some(res) => res##isLoggedIn ? () : redirectToLoginPage()
      }
    })
    | RedirectToLoginPage => SideEffects(_self => { Router.push("/login"); })
    | ChangePage(page, ignoreLayout) => Update({ page: page, ignoreLayout: ignoreLayout })
    }
  },

  render: self => {
    <Layout ignore_=self.state.ignoreLayout>
        {switch(self.state.page){
        | Index => <LaunchesPage />
        | Login => <LoginPage />
        | Launch(launchId) => <LaunchPage launchId=int_of_string(launchId) />
        | Profile => <ProfilePage />
        | Error404 => <LaunchesPage /> /* temporary */
        }}
    </Layout>
  }
}
