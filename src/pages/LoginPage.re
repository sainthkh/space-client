module LoginUser = [%graphql {|
  mutation login($email: String!) {
    login(email: $email)
  }
|}];

module LoginUserMutation = ReasonApollo.CreateMutation(LoginUser)


type res = ReasonApolloTypes.executionResponse(LoginUser.t);

let component = ReasonReact.statelessComponent("LoginPage");

let make = (_children) => {
  ...component,

  render: _self => {
    <LoginUserMutation>
      ...{
        (mutation, { result }) => {
          let login = email => {
            let query = LoginUser.make(~email=email, ());
            open Js.Promise;
            mutation(
              ~variables=query##variables,
              ()
            )
            |> then_((response:res) => {
              switch(response) {
              | Errors(_errors) => Js.log("Error")
              | EmptyResponse => Js.log("Empty")
              | Data(data) => {
                Dom.Storage.(localStorage |> setItem("token", data##login));
                LocalQuery.writeLogin(~client=GqlClient.instance, ~data={ "isLoggedIn": true }, ());
              }
              }
              ReasonReact.Router.push("/")
              
              resolve(response);
            })
            |> ignore
          };

          switch(result) {
          | Loading => <Loading />
          | Error(error) => <p>{ ReasonReact.string(error##message) }</p>
          | NotCalled => 
            <LoginForm login=login />
          | Data(_response) => 
            ReasonReact.null
          }
        }
      }
    </LoginUserMutation>
  }
}
