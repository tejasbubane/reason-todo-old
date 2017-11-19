let txt = ReasonReact.stringToElement;

type item = {
  title: string,
  completed: bool
};

type state = {items: list(item)};

type action =
  | AddItem;

let component = ReasonReact.reducerComponent("TodoApp");

let newItem = () => {title: "Add item from user", completed: false};

let make = (_children) => {
  ...component,
  initialState: () => {items: [{title: "Need to learn reasonml", completed: false}]},
  reducer: (action, {items}) =>
    switch action {
    | AddItem => ReasonReact.Update({items: [newItem(), ...items]})
    },
  render: ({state: {items}, reduce}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (txt("What to do?"))
        <button onClick=(reduce((_) => AddItem))> (txt("Add Item")) </button>
      </div>
      <div className="items"> (txt("Nothing")) </div>
      <div className="footer">
        (txt(string_of_int(numItems) ++ (numItems == 1 ? " item" : " items")))
      </div>
    </div>
  }
};
