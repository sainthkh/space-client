let styles = [%raw {| require("./Header.scss") |}]

let component = ReasonReact.statelessComponent("Header")

let make = (
  ~title: string="Space Explorer",
  _children
) => {
  ...component,

  render: _self => {
    <div className=styles##wrap>
      <img src="" className=styles##avatar alt="Space dog" />
      <div>
        <h2>{ ReasonReact.string(title) }</h2>
        <h5 className=styles##email>{ ReasonReact.string("email@email.com") }</h5>
      </div>
    </div>
  }
}
