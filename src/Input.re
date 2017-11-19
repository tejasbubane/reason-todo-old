let txt = ReasonReact.stringToElement;

type state = string;

let component = ReasonReact.reducerComponent("Input");

let valueFromEvent = (event) : string => (
                                           event
                                           |> ReactEventRe.Form.target
                                           |> ReactDOMRe.domElementToObj
                                         )##value;

let make = (~onSubmit, _children) => {
  ...component,
  initialState: () => "",
  reducer: (newText, _text) => ReasonReact.Update(newText),
  render: ({state: text, reduce}) =>
    <input
      value=text
      _type="text"
      placeholder="Write something to do"
      onChange=(reduce((e) => valueFromEvent(e)))
      onKeyDown=(
        (event) =>
          if (ReactEventRe.Keyboard.key(event) == "Enter") {
            onSubmit(text);
            reduce((_) => "", ())
          }
      )
    />
};
