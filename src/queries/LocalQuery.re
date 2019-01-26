module LoginConfig = {
  let query = {|
  query IsUserLoggedIn {
    isLoggedIn @client
  }
|};

  type t = {.
    "isLoggedIn": bool,
  };

  let parse = json => {
    open Jsonx;
    let obj = obj(json);

    { "isLoggedIn": obj->defaultBooleanIfNone("isLoggedIn", false) }
  }
}

module WriteLogin = ApolloClient.WriteQuery(LoginConfig);
module ReadLogin = ApolloClient.ReadQuery(LoginConfig);

let writeLogin = WriteLogin.make;
let readLogin = ReadLogin.make;