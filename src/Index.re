ReactDOMRe.renderToElementWithId(
  <ApolloProvider client=GqlClient.instance>
    <App />
  </ApolloProvider>, 
  "app");
ReasonReact.Router.push("");