let txt = ReasonReact.stringToElement;

type item = {
  id: int,
  title: string,
  completed: bool
};

let component = ReasonReact.statelessComponent("TodoItem");

let make = (~item, ~onToggle, _children) => {
  ...component,
  render: (_self) =>
    <div className="item">
      <input
        _type="checkbox"
        checked=(Js.Boolean.to_js_boolean(item.completed))
        onClick=((_e) => onToggle(item.id))
      />
      (txt(item.title))
    </div>
};
