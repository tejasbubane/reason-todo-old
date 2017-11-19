let txt = ReasonReact.stringToElement;

type state = {items: list(TodoItem.item)};

type action =
  | AddItem(string)
  | ToggleItem(int);

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);

let newItem = (title) : TodoItem.item => {
  lastId := lastId^ + 1;
  {id: lastId^, title, completed: false}
};

let renderList = (items, reduce) =>
  items
  |> List.map(
       (item: TodoItem.item) =>
         <TodoItem key=(string_of_int(item.id)) item onToggle=(reduce((id) => ToggleItem(id))) />
     )
  |> Array.of_list
  |> ReasonReact.arrayToElement;

let make = (_children) => {
  ...component,
  initialState: () => {items: [{id: 0, title: "Need to learn reasonml", completed: false}]},
  reducer: (action, {items}) =>
    switch action {
    | AddItem(title) => ReasonReact.Update({items: [newItem(title), ...items]})
    | ToggleItem(id) =>
      let newItems =
        List.map(
          (item: TodoItem.item) => item.id == id ? {...item, completed: ! item.completed} : item,
          items
        );
      ReasonReact.Update({items: newItems})
    },
  render: ({state: {items}, reduce}) => {
    let allItems = List.length(items);
    let completedItems =
      items |> List.filter((item: TodoItem.item) => item.completed) |> List.length;
    <div className="app">
      <div className="title">
        (txt("What to do?"))
        <Input onSubmit=(reduce((title) => AddItem(title))) />
      </div>
      <div className="items"> (renderList(items, reduce)) </div>
      <div className="footer">
        (
          txt(
            "Total: " ++ string_of_int(allItems) ++ ", Completed:" ++ string_of_int(completedItems)
          )
        )
      </div>
    </div>
  }
};
