# mcpserver_gui

Minimal MCP server (Streamable HTTP transport) used to test the MCP client
of TextAutoGenerateTextMcpProtocolCore. It is meant to be used with
`mcpclient_gui` (`tests/client`), but any MCP client can connect to it.

## Build

The application is built with the other tests (`BUILD_TESTING=ON`):

```bash
cd build-dev
ninja mcpserver_gui mcpclient_gui
```

## Run

Run it from the build directory, so the plugins and libraries of the build are
used instead of the installed ones:

```bash
cd build-dev/bin
export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
./mcpserver_gui                                   # listen on http://127.0.0.1:8765/mcp
./mcpserver_gui --url http://127.0.0.1:9000/mcp   # other port/path
```

The server starts automatically. The host must be `localhost` or an IP address.

The window shows every message received (`<--`) and sent (`-->`).

Buttons:

- **Start / Stop**: start or stop listening (URL can be changed when stopped).
- **Add/Remove "reverse" tool**: add or remove the `reverse` tool and send a
  `notifications/tools/list_changed` notification to the client.
- **Ping client**: send a `ping` request to the client (in the GET event stream).
- **Clear log**.

## What the server supports

| Method                     | Answer                                           |
|----------------------------|--------------------------------------------------|
| `initialize`               | Capabilities `tools` (listChanged), `prompts`, `resources` |
| `ping`                     | Empty result                                     |
| `tools/list`               | Paginated: 2 tools by page (`nextCursor`)        |
| `tools/call`               | See tools below                                  |
| `prompts/list`             | One prompt: `greeting` (argument `name`)         |
| `prompts/get`              | Message "Say hello to <name>"                    |
| `resources/templates/list` | One template: `file:///{path}`                   |
| `resources/list`           | Empty list                                       |
| other                      | JSON-RPC error -32601 (method not found)         |

Tools:

| Tool           | Arguments                  | Result                                      |
|----------------|----------------------------|---------------------------------------------|
| `echo`         | `text` (string)            | Same text                                   |
| `add`          | `a`, `b` (numbers)         | Sum                                         |
| `current_time` | none                       | Current date/time (ISO)                     |
| `fail`         | none                       | Tool error (`isError: true`)                |
| `slow`         | `milliseconds` (integer, default 2000) | Answers after the delay; not answered if the client sends `notifications/cancelled` |
| `reverse`      | `text` (string)            | Reversed text (only when added with the button) |

An unknown tool gives the JSON-RPC error -32602.

## Test with mcpclient_gui

Interactive:

```bash
./mcpserver_gui &
./mcpclient_gui
```

Click **Connect**, then use the buttons (Ping, List tools, Call tool with
JSON arguments such as `{"text": "hello"}`…), or **Run all checks**.

Automatic (for scripts): `--autorun` connects, runs all checks, prints
`PASS`/`FAIL` on stdout and exits with 0 if all checks passed, 1 otherwise:

```bash
./mcpserver_gui --url http://127.0.0.1:18765/mcp &
./mcpclient_gui --autorun --url http://127.0.0.1:18765/mcp
kill %1
```
