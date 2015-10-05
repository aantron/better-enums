## Design decisions FAQ

$be pushes at the edges of what is possible in standard $cxx, and I've had to
make some difficult decisions as a result. You can imagine the set of
potential reflective enum implementations as a space, with axes such as "concise
syntax," "uniform interface," "compilation speed," "run-time performance," and
so on. As is typical in engineering, the constraints are such that as you move
to extremes along one axis, you have to retreat along others &mdash; for
example, some desirable aspects of concise syntax conflict with having a uniform
interface, which is nonetheless good for teachability, and compile-time
performance is, in some ways, at odds with run-time performance.

So, there are many variations possible on $be, and, in fact, I have tried and
maintained a few. This page describes how I chose the one that is published.
The choices are debatable, but I am attempting to record the debate. Hopefully,
this will either convince you that I have made a good choice, or, if you
disagree, you will have a good starting point for discussion, or even for
implementing an alternative.

I am always looking for new arguments and approaches. If you have an idea,
comment, criticism, please do [let me know][contact].

$internal_toc

### Why do enum members have underscores?

Enum members such as `_to_string` occupy the same scope as the names of
constants declared by the user. I chose to prefix members with underscores to
lessen the chances of collision. For example, take `_valid`, and suppose it was
`valid` instead. That would make this enum impossible:

    <em>BETTER_ENUM(Status, char, valid, invalid)</em>

because the constant `Status::valid` would clash with the member
`Status::valid`.

Of course, users could try to declare constants with underscores as well, but I
find it easier to ask users not to do that, rather than ask them to worry about
a potentially growing set of reserved names, which they wouldn't fully know even
for a single version of Better Enums, without frequently looking at the API
documentation.

Alternatives to this involve separating the namespaces occupied by members and
constants. I don't think increasing nesting is an option, since nobody wants to
write `Status::values::valid` or `Status::operations::valid`. I don't think
moving constants out of `Status` is a good idea, since scoped constants is a
feature of Better Enums, which is especially important for $cxx98 usage.

This leaves the possibility of moving the operations performed by the members
into traits types, i.e. something like `traits<Status>::valid`. That is an
interesting option, and it has [its own section][traits]. I have tried it, but
the verbosity increase is much greater than the benefit of dropping underscores,
so I chose not to do it.

### Why does Better Enums use a macro at all?

Better Enums needs to turn the names of declared constants into strings, and I
don't believe there is any way to do this in standard $cxx except by using the
preprocessor's macro parameter stringization operator (`#`). So, at the top
level, Better Enums has to provide a macro. I am, however, trying to keep the
user-facing macros to a minimum; in particular there is only one.

I think that's the best that is possible. Furthermore, apart from the macro
itself, the declaration looks very similar to a $cxx11 `enum` declaration, with
an underlying type, comma-separated constant list, and the same support for
initializers as built-in enums. So, I am trying to keep even this one macro out
of the user's way. I wouldn't accept any change that involved turning the
declaration into a preprocessor sequence or tuple, i.e. something like

    <em>BETTER_ENUM(Channel, int, (Red)(Green)((Blue)(5)))</em>

even if it promised extra capabilities.

Better Enums uses additional macros internally, for two main purposes: to do the
actual work of stringizing the declared constants and assembling them into
arrays, and to configure itself by detecting which compiler it is running on.

I am not a fan of gratuitous macros, but in these cases they are unavoidable,
and, indeed, I am grateful for the stringization operator.

<a id="NoEnumInsideClass"></a>
### Why is it not possible to declare a Better Enum inside a class?

This is due to an interaction between linkage and `constexpr`.

1. Better Enums is a header-only library that declares arrays with static
   storage, such as the array of constant names for each declared enum. Such
   arrays can be declared in namespace scope, in class scope, or in function
   scope, but they also need to be defined somewhere.

   If `BETTER_ENUM` is to be usable in both namespace and class scope, it
   already can't assume that it can declare arrays in namespace scope, since if
   `BETTER_ENUM` is used in a class, its entire expansion will be enclosed in
   the declaration of that class.

   That leaves class scope and function scope. If the arrays are declared in
   class scope, there needs to be a separate definition of them in some
   translation unit. This is too burdensome for the user, because the separate
   definition would involve repetition of the constants in the macro parameter
   list, creating exactly the type of maintenance problem that Better Enums is
   trying to eliminate.

   Function scope is the only viable option remaining after considering linkage
   constraints. Each array can be wrapped in a static function, which has a
   static local variable, which is initialized with the array. The functions can
   be called to get references to the arrays.

   However....

2. These arrays need to be accessible to `constexpr` code in $cxx11, and
   `constexpr` functions are not allowed to have static local variables.

Ironically, this seems like one place where $cxx98 is more "flexible," but only
for the reason that compile-time usage of Better Enums is not supported in
$cxx98.

<a id="Traits"></a>
### Should Better Enums provide enum "objects" or traits types?

A Better Enum value is an "object," whose memory representation is the same as
its underlying type. For example,

    <em>BETTER_ENUM(Channel, int, Red, Green, Blue)</em>

expands to something like

    <em>struct Channel {
        enum _enumerated : int { Red, Green, Blue };
        int _value;</em>
        // Strings array, _to_string, _from_string, etc.
    <em>};</em>

---

There is an alternative interpretation, in which the Better Enums library
generates enum traits instead, i.e. the generated arrays and members sit
alongside built-in enums instead of wrapping them:

    <em>BETTER_ENUM(Channel, int, Red, Green, Blue)</em>

generates

    <em>enum class Channel : int { Red, Green, Blue };</em>

    <em>template <>
    struct ::better_enums::traits<Channel> {
        using _enumerated = Channel;</em>
        // Strings array, to_string, from_string, etc.
    <em>};</em>

---

There are a number of advantages to the traits approach.

- The underscore prefixes can be dropped from member names, since they no longer
  share a namespace with user-declared constants.
- The interface, at first glance, becomes more uniform, since now every member
  is a static member of the traits type. Without traits, `_to_string` is a
  non-static member, while `_from_string` is a static member.
- `Channel` is one of the language's own enum types, instead of some mystery
  type provided by Better Enums. This may make it easier to understand. It also
  eliminates the problem with different syntaxes for `switch` statements
  described [here][implicit].

However, it also introduces some difficulties.

- The syntax is more verbose, since everything becomes a member of the traits
  type. For example, instead of `Channel::_from_string()`, you get
  `better_enums::traits<Channel>::from_string()`. The underscore may be
  unpleasant, but so far I have preferred the underscore to boilerplate.
- The uniform interface ends up getting wrapped behind functions anyway, for the
  sake of type inference. For example, the "naked" `to_string` function is
  called as `better_enums::traits<Channel>::to_string(channel)`, which is
  redundant, because the compiler could infer the type parameter `Channel` if it
  was the parameter of the function instead of the traits type. So, the obvious
  thing is to define such a wrapper function, which can then be called as
  `better_enums::to_string(channel)`. No such function can be easily defined for
  `from_string` and other `from_*` functions, however, because the type
  parameters can't be inferred from arguments. So, the signatures of `to_*` and
  `from_*` functions again effectively diverge, negating this advantage of
  traits. The closest I can get with wrappers is
  `better_enums::from_string<Channel>`, which has the same signature only in the
  formal sense, i.e. modulo the difference in type inference.

  I actually think there is a way to infer the type parameter from the return
  type, similar to how it is done [here][infer], but that will not be suitable
  for all contexts, and the user may be surprised by ambiguous resolution error
  messages when it is not.
- Scoped constants are lost for $cxx98 unless Better Enums again wraps them in a
  generated type, though it will be more lightweight than a full Better Enum of
  the non-traits approach.
- Traits types must be specialized in either the same namespace scope they are
  declared in, or in an enclosing scope. This makes it impossible to declare an
  enum and specialize traits for it in a user's custom namespace.

Despite the disadvantages listed just above, I consider the traits approach
interesting &mdash; it's a close call. There is an
[out-of-date branch][traits-branch] containing a traits version of Better Enums.
You can see some of the usage in its [samples][traits-samples] directory. I may
update it from time to time, especially if there is interest.

### Why does Better Enums use linear scans for lookup?

It seems that Better Enums needs to use the same algorithms at compile time as
at run time, because I have not found a way (and doubt there is one) to
determine, during the execution of a `constexpr` function, whether it is
executing at compile time or at run time. So, whatever data structures I use to
accelerate lookup, I have to generate them at compile time, to be available as
early as possible.

I tried to generate various data structures at compile time, but so far,
generation has been too slow. The fastest algorithm so far, a compile-time merge
sort based on template parameter packs, took over 100ms to run on the constant
set of a large enum. I would have to run three of these per enum &mdash; for the
constants, for the names, and for the names with case-insensitive comparison.
This results in a 300ms slowdown per enum, which is not acceptable, given that
on my system the same compiler takes 370ms to process `iostream`, and less than
10ms to process an enum without acceleration data structures. Declaring five
large enums with accelerated lookup would take 1.5 seconds of compilation time.
This doesn't scale to large projects with many translation units.

I am continuing to look for faster algorithms or better approaches, so faster
lookup may be coming to Better Enums in the future.

So far, I have tried Boost.MPL sort, Eric Niebler's Meta sort, my own selection
sort based on `constexpr`, and an insertion and merge sort based on parameter
packs. I cannot use (Boost?).Hana sort, because that requires $cxx14. I am also
considering various hash table-like data structures, and providing two sets of
interfaces for compile-time and run-time usage, which is something I would
really rather not have to do. The latter option would be worth considering,
however, if I measured a significant improvement in running time from better
data structures &mdash; something I haven't gotten to yet because there doesn't
seem to be a data structure to measure that is not disqualified by the speed of
generation.

### Why not use indices for the representation?

Representing Better Enum values by their indices in the declaration list seems
like a tempting solution for the problem of having multiple constants with the
same numeric value. It also speeds up some operations. For example, if a Better
Enum is simply an index, then getting its string representation is simply
indexing an array, rather than some kind of data structure lookup.

    // Representations 0, 1, 2, 3 instead of 1, 2, 3, 1.
    <em>BETTER_ENUM(Kind, int, A = 1, B, C, D = A)</em>

Choosing this approach has serious drawbacks.

- The data structure lookup has simply been moved to another place. It now takes
  time to convert from a literal `Kind::D` to a Better Enum.
- It is still impossible to disambiguate between the literals `Kind::D` and
  `Kind::A` (1 and 1). Only the Better Enums objects of type `Kind` that
  represent `D` and `A` are different from each other (0 and 3). This is not
  only a technical problem, but is also quite unintuitive.
- Treating a Better Enum represented by an index as untyped memory produces
  surprising results. This makes Better Enums much less useful with functions
  such as `fwrite`. Worse, Better Enums become sensitive to declaration order
  even when initializers are given explicitly. Using indices for the
  representation makes it difficult to maintain compatibility with external
  protocols and file formats.

[contact]: ${prefix}Contact.html
[traits]: #Traits
[implicit]: ${prefix}OptInFeatures.html#StrictConversions
[infer]: ${prefix}demo/SpecialValues.html
[traits-branch]: $repo/tree/traits
[traits-samples]: $repo/tree/traits/samples

%% description = Better Enums design decisions and tradeoffs.
