open Utils;
open Types;

let component = ReasonReact.statelessComponent("Node");

let make =
    (
      ~node_id: node_id,
      ~definition: definition,
      ~position: point,
      ~emit: graph_action => unit,
      _children,
    ) => {
  ...component,
  render: _self => {
    let definition =
      switch (definition) {
      | Graph(graph_definition) => graph_definition
      };

    let documentation = getDocumentation(definition);

    <div className="node" style=(positionStyle(position))>
      <div className="name"> (ReasonReact.string(documentation.name)) </div>
      (
        renderMap(
          ((nib_id, name)) =>
            <div className="input" key=nib_id>
              (ReasonReact.string(name))
              <div
                className="sink nib"
                onMouseDown=(
                  event =>
                    emit(
                      StartDrawing({
                        pointer_id: "mouse",
                        drawing_connection: {
                          nib_connection: NodeConnection({nib_id, node_id}),
                          point: pointFromMouse(event),
                          startIsSource: false,
                        },
                      }),
                    )
                )
                onMouseUp=(
                  _ =>
                    emit(
                      FinishDrawing({
                        pointer_id: "mouse",
                        nib_connection: NodeConnection({nib_id, node_id}),
                        isSource: false,
                      }),
                    )
                )
              />
            </div>,
          documentation.inputNames,
        )
      )
      (
        renderMap(
          ((nib_id, name)) =>
            <div className="output" key=nib_id>
              <div
                className="source nib"
                onMouseDown=(
                  event =>
                    emit(
                      StartDrawing({
                        pointer_id: "mouse",
                        drawing_connection: {
                          nib_connection: NodeConnection({nib_id, node_id}),
                          point: pointFromMouse(event),
                          startIsSource: true,
                        },
                      }),
                    )
                )
                onMouseUp=(
                  _ =>
                    emit(
                      FinishDrawing({
                        pointer_id: "mouse",
                        nib_connection: NodeConnection({nib_id, node_id}),
                        isSource: true,
                      }),
                    )
                )
              />
              (ReasonReact.string(name))
            </div>,
          documentation.outputNames,
        )
      )
    </div>;
  },
};
