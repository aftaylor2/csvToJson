
# CSV to JSON Converter

This project provides a simple C program that converts CSV data to JSON and makes an optional HTTPS POST request to a specified API endpoint. Additionally, the project includes a test suite to verify the functionality of the CSV to JSON conversion

## Notice

This project is currently a non-production, experimental endeavor. While functional, it may not yet meet the standards required for production use. It was developed as an intellectual exercise to enhance and refresh my skills and familiarity with the C programming language and associated developer tooling.

## Project Structure

```text
csvToJson/
├── bin/
│   ├── csvToJSON
│   └── test_csvToJSON
├── data/
│   └── test.csv
├── src/
│   ├── csvToJSON.c
│   ├── csvToJSON.h
│   ├── csvToJSON_lib.c
│   └── test_csvToJSON.c
├── .vscode/
│   └── settings.json
├── .clang-format
├── .editorconfig
├── .gitignore
├── CONTRIBUTING.md
├── configure
├── LICENSE
├── Makefile
└── README.md

```

- **bin/**: Directory containing the compiled binaries.
- **data/**: Directory containing test CSV files.
- **src/**: Directory containing the source code files.
  - **csvToJSON.c**: Contains the `main` function and the HTTPS POST request logic.
  - **csvToJSON.h**: Header file with function declarations.
  - **csvToJSON_lib.c**: Contains the CSV to JSON conversion logic.
  - **test_csvToJSON.c**: Test program for the CSV to JSON conversion.
- **vscode/**: Directory containing VSCode settings.
- **settings.json**: VSCode settings for consistent code formatting.
- **.clang-format**: ClangFormat configuration for code style enforcement.
- **.editorconfig**: EditorConfig file for consistent coding styles across different editors.
- **.gitignore**: File specifying which files and directories to ignore in version control.
- **CONTRIBUTING.md**: Guidelines for contributing to the project.
- **configure**: Script to generate the Makefile.
- **LICENSE**: License file containing the MIT license text.
- **Makefile**: Build configuration for the project using GNU Make.
- **CMakeLists.txt**: Alternative / OPTIONAL build config for the project.
- **README.md**: File providing information about the project. (*This file!*)

## Prerequisites

- GCC (GNU Compiler Collection)
- libcurl development libraries

### Non Unix-like Operating Systems

This project is designed for Unix-like operating systems such GNU/Linux, MacOS, BSD.

For non-Unix-like operating systems such as Windows, you may need to use compatibility layers or tools such as [Cygwin](https://www.cygwin.com/) or [WSL](https://learn.microsoft.com/en-us/windows/wsl/about) (Windows Subsystem for Linux) to compile and run the project.

## Setup

Build the project using [GNU Make](https://www.gnu.org/software/make/):

1. **Make the `configure` script executable:**

    ```sh
    chmod +x configure
    ```

2. **Run the `configure` script to generate the Makefile:**

    ```sh
    ./configure
    ```

3. **Build the project and the tests:**

    ```sh
    make
    ```

Optionally, you may build the project using [CMake](https://cmake.org/cmake/help/latest/guide/tutorial/index.html):

1. **Build the project:**

    ```sh
    cmake CMakeLists.txt
    ```



## Running the Program

**Usage:**

```sh
./csvToJSON <csv_file_path> [<api_endpoint>] [<bearer_token>]
```

To convert a CSV file to JSON

```sh
./csvToJSON <csv_file_path>
```

To convert a CSV file to JSON and send the JSON to a public endpoint on a server via HTTPS:

```sh
./csvToJSON ../data/test.csv https://api.example.com/endpoint
```

To convert a CSV file to JSON and send the JSON to an endpoint requiring Authentication:

```sh
./csvToJSON ../data/test.csv https://api.example.com/endpoint your_bearer_token
```

## Running the Tests

To run the tests, use the following command:

```sh
make test
```

This will compile and execute the test program `test_csvToJSON`, verifying the CSV to JSON conversion.

## Example CSV File

`test.csv`:

```csv
firstName,lastName,dob
John,Doe,1985-08-01
Jane,Doe,1991-04-20
```

## Expected JSON Output

For the provided `test.csv`, the expected JSON output is:

```json
[{"firstName":"John","lastName":"Doe","dob":"1985-08-01"},{"firstName":"Jane","lastName":"Doe","dob":"1991-04-20"}]
```

## License

This project is licensed under the MIT License.

## Contributing

Feel free to submit issues or pull requests if you find any bugs or want to add new features.

Sure! Here's an improved version of the TODO section:

---

## TODO

Refactor the project to adhere more closely to the UNIX philosophy by separating concerns. Specifically, remove the HTTP API request functionality from this tool. Instead, create a standalone tool dedicated to making HTTP requests. The JSON output from this tool can be piped to the HTTP request tool, allowing for greater modularity and flexibility.

1. **Create a Separate HTTP Request Tool**:
    - Develop a standalone tool that handles HTTP requests.
    - Use CLI flags or parameters to specify the hostname and authentication details.

2. **Leverage Existing Tools**:
    - Alternatively, use existing standardized tools such as `cURL` to handle HTTP requests.

3. **Example Usage**:
    - Pipe the JSON output from this tool to the HTTP request tool.
    - Example: `./csvToJSON file.csv | ./httpRequester --hostname example.com --auth "Bearer token"`
    - Or using `cURL` directly: `./csvToJSON file.csv | curl -X POST -H "Content-Type: application/json" -H "Authorization: Bearer token" -d @- https://api.example.com`

By modularizing the functionality, we can create more reusable and maintainable components that align with the UNIX philosophy of building simple, single-purpose tools that work together to become capable of performing complex tasks.

## Author

[Andrew Taylor](https://github.com/aftaylor2)
