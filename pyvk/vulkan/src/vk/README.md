# Preamble

The folders are based on object/structure types. They contain the files that operate on and around the object types.

The header file `(.h)` defines the Python class structure, declares the type object. This type object can be used in other classes for instantiation.

The source file `(.c)` defines the Python class members, defines the type object, and its functions and other helper functions.

Every Python class structure holds a instance of the vulkan structure it is wrapping around. This instance acts as a holder for the values recieved through the `init` funciton, and can be passed on to the raw vulkan functions or structures as needed.

