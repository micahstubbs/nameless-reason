open Types;

let component = ReasonReact.statelessComponent("Graph");

let make = (~definition, ~definitions, _children) => {
  ...component,
  render: _self => {
    let getDefinition = definition_id =>
      DefinitionMap.find(definition_id, definitions);
    let getNodeDefinition = node => getDefinition(node.definition_id);
    let getDocumentation = definition =>
      LanguageMap.find("en", definition.documentation);

    let documentation = getDocumentation(definition);
    let inputs = NibMap.bindings(documentation.inputNames);
    let outputs = NibMap.bindings(documentation.outputNames);
    let nodes = NodeMap.bindings(definition.implementation.nodes);

    let renderList = list => ReasonReact.array(Array.of_list(list));

    <div>
      (ReasonReact.string(documentation.name))
      (
        renderList(
          List.map(
            ((nib_id, name)) =>
              <div key=nib_id> (ReasonReact.string(name)) </div>,
            inputs,
          ),
        )
      )
      (
        renderList(
          List.map(
            ((nib_id, name)) =>
              <div key=nib_id> (ReasonReact.string(name)) </div>,
            outputs,
          ),
        )
      )
      (
        renderList(
          List.map(
            ((node_id, node)) => {
              let definition =
                switch (getNodeDefinition(node)) {
                | Graph(graph_definition) => graph_definition
                };
              let documentation = getDocumentation(definition);
              <div key=node_id>
                (ReasonReact.string(documentation.name))
              </div>;
            },
            nodes,
          ),
        )
      )
    </div>;
  },
};
