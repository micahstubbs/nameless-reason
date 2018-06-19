open Types;
open Utils;

let component = ReasonReact.statelessComponent("Graph");

let make = (~definition, ~definitions, _children) => {
  ...component,
  render: _self => {
    let getDefinition = definition_id =>
      DefinitionMap.find(definition_id, definitions);
    let documentation = getDocumentation(definition);
    let inputs = NibMap.bindings(documentation.inputNames);
    let outputs = NibMap.bindings(documentation.outputNames);
    let nodes = NodeMap.bindings(definition.implementation.nodes);

    <div>
      (ReasonReact.string(documentation.name))
      (
        renderMap(
          ((nib_id, name)) =>
            <div key=nib_id> (ReasonReact.string(name)) </div>,
          inputs,
        )
      )
      (
        renderMap(
          ((nib_id, name)) =>
            <div key=nib_id> (ReasonReact.string(name)) </div>,
          outputs,
        )
      )
      (
        renderMap(
          ((node_id, node)) =>
            <Node
              key=node_id
              definition=(getDefinition(node.definition_id))
            />,
          nodes,
        )
      )
    </div>;
  },
};
