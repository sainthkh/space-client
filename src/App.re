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
    <div>
      { ReasonReact.string("App") }
    </div>
  }
}
