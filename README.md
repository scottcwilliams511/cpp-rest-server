# Cpp Rest Server

## Usage

This depends on cpprestsdk: https://github.com/Microsoft/cpprestsdk

To install (mac), you will need to install it and its dependencies:

```sh
brew install cpprestsdk openssl boost
```

You may notice output similar to this while installing openssl or boost:

```
openssl is keg-only, which means it was not symlinked into /usr/local,
because Apple has deprecated use of OpenSSL in favor of its own TLS and crypto libraries.

If you need to have openssl first in your PATH run:
  echo 'export PATH="/usr/local/opt/openssl/bin:$PATH"' >> ~/.bash_profile

For compilers to find openssl you may need to set:
  export LDFLAGS="-L/usr/local/opt/openssl/lib"
  export CPPFLAGS="-I/usr/local/opt/openssl/include"
```

Take note of the LDFLAGS and CPPFLAGS as they are needed for building. You may need to change the values in the makefile if they differ from the output you got.

Now, run this:

```
make run
```

The program should be built and started. Visit this url to test it: http://localhost:3000/api/v1/test?v=1&t=2

If should reply with this: `{"foo":"bar"}`


## Visual Studio Code Usage

You may want to have vscode generate the file `.vscode/c_cpp_properties.json`.
In there, you should set this line:

```json
{
    "configurations": [
        {
            // ...
            "includePath": [
                // ...
                "/usr/local/opt/openssl/include"
            ]
        }
    ]
}
```

Adding that line will fix include errors. You may need to change that value depending on where openssl is installed.

To build and run the server, switch to the debug interface in vscode and run `Build + debug server`. This will do exactly what it says. You can debug the server with breakpoints.
