let styles = [%raw {| require("./Header.scss") |}]

let component = ReasonReact.statelessComponent("Header")

let make = (
  ~title: string="Space Explorer",
  ~image="",
  _children
) => {
  ...component,

  render: _self => {
    <div className=styles##wrap>
      <img src=image className=styles##avatar alt="Space dog" />
      <div>
        <h2>{ ReasonReact.string(title) }</h2>
        <h5 className=styles##email>{ ReasonReact.string("email@email.com") }</h5>
      </div>
    </div>
  }
}
