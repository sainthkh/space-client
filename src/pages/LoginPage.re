module LoginUser = [%graphql {|
  mutation login($email: String!) {
    login(email: $email)
  }
|}];

module LoginUserMutation = ReasonApollo.CreateMutation(LoginUser)

let component = ReasonReact.statelessComponent("LoginPage");

let make = (_children) => {
  ...component,

  render: _self => {
    <ApolloConsumer>
      ...{
        _client => {
          <LoginUserMutation>
            ...{
              (_login, { result }) => {
                switch(result) {
                | Loading => <Loading />
                | Error(error) => <p>{ ReasonReact.string(error##message) }</p>
                | NotCalled => 
                  <LoginForm login={_a => ()} />
                | Data(_response) => 
                  <p>{ ReasonReact.string("OK") }</p>
                }
              }
            }
          </LoginUserMutation>
        }
      }
    </ApolloConsumer>
  }
}
