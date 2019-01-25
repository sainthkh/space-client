let styles: LoginFormStyles.definition = [%raw {| require("./LoginForm.scss") |}]

type state = {
  email: string,
};

type action = 
  | UpdateEmail(string)
  | Login;

let component = ReasonReact.reducerComponent("LoginForm");

let make = (
  ~login: string => unit,
  _children
) => {
  ...component,
  initialState: () => {
    email: "",
  },

  reducer: (action: action, state: state) => {
    switch(action) {
    | UpdateEmail(email) => ReasonReact.Update({ email: email })
    | Login => ReasonReact.UpdateWithSideEffects({ email: "" }, _self => {
      login(state.email)
    })
    }
  },

  render: self => {
    let onChange = event => {
      let value = event->ReactEvent.Form.target##value;
      self.send(UpdateEmail(value));
    }

    let onClick = event => {
      self.send(Login);
      event->ReactEvent.Synthetic.preventDefault;
    };

    <div className=styles##wrap>
      <div className=styles##header>
      </div>
      <h1 className=styles##heading>{ ReasonReact.string("Space Explorer") }</h1>
      <form className=styles##loginForm>
        <input type_="email" placeholder="your@email.com" className=styles##field onChange />
        <button className="btn" onClick>{ ReasonReact.string("Log in") }</button>
      </form>
    </div>
  }
}