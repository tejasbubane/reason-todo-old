let txt = ReasonReact.stringToElement;

type state = {items: list(TodoItem.item)};

type action =
  | AddItem;

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);

let newItem = () : TodoItem.item => {
  lastId := lastId^ + 1;
  {id: lastId^, title: "Add item from user", completed: false}
};

let renderList = (items) =>
  items
  |> List.map((item: TodoItem.item) => <TodoItem key=(string_of_int(item.id)) item />)
  |> Array.of_list
  |> ReasonReact.arrayToElement;

let make = (_children) => {
  ...component,
  initialState: () => {items: [{id: 0, title: "Need to learn reasonml", completed: false}]},
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
      <div className="items"> (renderList(items)) </div>
      <div className="footer">
        (txt(string_of_int(numItems) ++ (numItems == 1 ? " item" : " items")))
      </div>
    </div>
  }
};
