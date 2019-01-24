let component = ReasonReact.statelessComponent("ActionButton");

let make = (
  ~isBooked: bool,
  ~isInCart: bool,
  _children
) => {
  ...component,

  render: _self => {
    <button className="btn">
      { 
        let text = isBooked ?
          "Cancel this trip" :
            isInCart ?
              "Remove from cart" :
              "Add to cart"
        ReasonReact.string(text) 
      }
    </button>
  }
}
