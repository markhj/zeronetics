@page file-system File system

Working with paths, directories and files in Zeronetics require
knowledge of only two classes. Let's get started!

## 📂 Paths

ZEN::Path is instantiated with a relative or absolute path that
either does or doesn't exist. Both of these will work:

````cpp
ZEN::Path file1("existing-file.txt");
ZEN::Path file2("file-does-not-exist.txt");
````

But to check whether the path actually exists, you can use ZEN::Path::exists:

`````cpp
if (file1.exists()) {
    // ...
}
`````

### Other useful functions

- ZEN::Path::isDirectory
- ZEN::Path::isFile
- ZEN::Path::getAbsolute

## 📄 Files

### Instantiating

There are several ways to instantiate a ZEN::File object.

You can create one directly from ZEN::Path:

````cpp
ZEN::File myFile(ZEN::Path("/path/to/file"));
````

You can use the ZEN::File::load method which either returns
the created ``File`` object, or ``std::nullopt`` if:

- The path is a directory
- The path doesn't exist

````cpp
std::optional<ZEN::File> myFile = ZEN::File::load("/path/to/file");
````

Last, but not least, you can use ZEN::File::loadOrCreate, which
either returns the existing file, or creates it and _then_ returns it.

````cpp
ZEN::File myFile = ZEN::File::loadOrCreate("/path/to/file");
````

@warning If ``loadOrCreate`` is applied to an existing directory,
a critical-level message is raised.

### Get file data

You can store all the contents of a file in a std::string using
ZEN::File::getData.

The methods return a ZEN::Result with a ``std::string``.

Example:

````cpp
Result<std::string> data = myFile.getData();
if (data.isError()) {
    // Error handling
} else {
    // Do what needs to be done with the file contents
}
````

### Append to file

You can append data to a file using ZEN::File::append.

````cpp
ZEN::File myFile = /* Create instance of File */;
        
myFile.append("Adding data to the file");
````

@note You need to manage line-breaks in the file on your own.
``append`` will not add any line-breaks on its own.
