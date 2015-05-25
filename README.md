# Preoop
Object orientation implemented in C at compile time via the preprocessor (mostly).

Object instances are allocated on the heap.

Requires GCC 4.9 or above due to dependency on C11's `_Generic`.

## Usage
Include `preoop.h`.

Create an `objects` macro containing an entry for every object. Make sure all entries except for the last one have commas. For example, to have 3 objects called `Object1`, `Object2` and `Object3`:

    #define objects(a, b) objectList(a,\
        objectEntry(Object1, b),\
        objectEntry(Object2, b),\
        objectEntry(Object3, b)\
    )

Declare your objects:

    object {
        int a;
    } Object1;
    
    object {
        int b;
    } Object2;
    
    object {
        int c;
    } Object3;

Add methods to your objects:

    void method(Object1, doSomething) {
        self->a++;
    }

All objects must have an `init` method which returns its `self`:

    Object1 *method(Object1, init) {
        return self;
    }

Now you can create definitions of pointers to your objects, these are known as a `Object Instance`s:

    Object1 *myObject;

Before you can use an object instance, you must invoke `new` on it:

    myObject = new(Object1);

This will allocate memory for the object, and call its `init` method.

To invoke further methods on an object instance, use the `invoke` macro:

    invoke(myObject, doSomething);

Once you are finished with your object instance, you must `free` it:

    free(myObject);

For a complete demonstration of Preoop, see `sample.c`.

## How does it work?
Methods are essentially functions with the addition of `self` as the first parameter, and the name of the object appended to the name of the function to avoid conflict.

For example, this method:

    void method(foo, printPosition) {
        printf("X: %d\nY: %d\n", self->x, self->y);
    }

Is processed into:

    void printPosition_foo(foo *self) {
        printf("X: %d\nY: %d\n", self->x, self->y);
    }

And all `invokes` are processed from:

    invoke(bar, printPosition);

To:

    printPosition_foo(bar);