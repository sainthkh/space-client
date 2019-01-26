let styles = [%raw {| require("./Layout.scss") |}]
let component = ReasonReact.statelessComponent("Layout")

let make = (
  ~ignore_,
  children
) => {
  ...component,

  render: _self => {
    switch(ignore_){
    | true => 
      <div>...children</div>
    | false => 
      <>
        <div className=styles##bar></div>
        <div className=styles##container>
          ...children
        </div>
        <Footer />
      </>
    }
  }
}
