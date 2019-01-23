let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();
let httpLink =
  ApolloLinks.createHttpLink(~uri="http://localhost:4000/graphql", ());
let client =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());

ReactDOMRe.renderToElementWithId(
  <ApolloProvider client=client>
    <App />
  </ApolloProvider>, 
  "app");
ReasonReact.Router.push("");