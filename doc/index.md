Better Enums is a single header file that causes your compiler to generate
*reflective* enum types. This makes it easy to translate between enums and
strings, and much more.

Here's how to use a Better Enum:

<div class="splash">
  <pre class="left">enable

declare


parse
print


count
iterate



switch






safe cast


at compile time</pre>
  <pre class="right"><em>#include</em> &lt;<em>enum.h</em>&gt;

<em>ENUM</em>(<em>Channel</em>, <em>int</em>, <em>Red</em> = <em>1</em>, <em>Green</em>, <em>Blue</em>)


Channel     c = <em>Channel::_from_string("Red")</em>;
const char  *s = <em>c._to_string()</em>;


size_t      n = <em>Channel::_size</em>;
<em>for</em> (<em>Channel c</em> : <em>Channel::_values()</em>)
    run_some_function(<em>c</em>);


<em>switch</em> (<em>c</em>) {
    <em>case Channel::Red</em>:    // ...
    <em>case Channel::Green</em>:  // ...
    <em>case Channel::Blue</em>:   // ...
}


Channel     c = <em>Channel::_from_integral(3)</em>;


<em>constexpr</em> Channel c = <em>Channel::_from_string("Blue")</em>;</pre>
</div>

Jump to the [tutorial](${prefix}tutorial/HelloWorld.html) to see a complete
working example.

### What do you get?

<ul class="blurbs">
  <li class="even">
    <strong>Uniform interface for $cxx98 and $cxx11</strong>
    <em>Scoped, sized, reflective enums for $cxx98.</em>
  </li>
  <li>
    <strong>Compile-time reflection</strong>
    <em>
      Have the compiler do additional enum processing using your own
      templates or <code>constexpr</code> functions.
    </em>
  </li>

  <li class="even">
    <strong>Non-contiguous sequences</strong>
    <em>
      Iteration and count much easier to maintain than with an extra "count"
      constant and making assumptions.
    </em>
  </li>
  <li>
    <strong>Plays nice with <code>switch</code></strong>
    <em>
      Use a Better Enum like a built-in <code>enum</code>, and still have the
      compiler do case checking.
    </em>
  </li>

  <li class="even">
    <strong>Unobtrusive syntax</strong>
    <em>
      No ugly macros. Use initializers just like with built-in
      <code>enums</code>. Generated members have underscores to avoid conflicts
      with your constant names.
    </em>
  </li>
  <li>
    <strong>Don't repeat yourself</strong>
    <em>
      No more unmaintanable maps or <code>switch</code> statements for
      converting enums to strings.
    </em>
  </li>

  <li class="even">
    <strong>No build-time generator needed</strong>
    <em>
      Just include <code>enum.h</code>. It's a metaprogram executed by your
      compiler.
    </em>
  </li>
  <li>
    <strong>Fast compilation</strong>
    <em>
      Much less impact on build time than even just including
      <code>iostream</code>.
    </em>
  </li>

  <li class="even">
    <strong>No external dependencies</strong>
    <em>
      Uses standard $cxx and supported on major compilers. Installation is
      simple &mdash; just download <code>enum.h</code>.
    </em>
  </li>
  <li>
    <strong>Free and open source</strong>
    <em>
      Released under the BSD license for use in any project, free or commercial.
    </em>
  </li>
</ul>

<div class="hack"></div>

### It's what built-in enums ought to do.

The library notionally <em>extends</em> $cxx, adding oft-needed features.

<ul class="blurbs act">
  <li class="even">
    <strong>Download <a $download><code>enum.h</code></a></strong>
    <em>
      Current version: $version<br />
      To install, just add the file to your project.
    </em>
  </li>
  <li>
    <strong>Visit on <a href="$repo">GitHub</a></strong>
    <em>
      Follow development, report issues, and let me know if you find this
      library useful!
    </em>
  </li>
</ul>

<div class="hack"></div>

### Resources

<ul class="blurbs resources">
  <li class="even">
    <a id="Tutorial"></a>
    <strong>Tutorial</strong>
    <ol>
      $tutorial_toc
    </ol>
  </li>
  <li>
    <strong>Reference</strong>
    <ul>
      <li><a href="${prefix}ApiReference.html">API reference</a></li>
      <li><a href="${prefix}CompilerSupport.html">Compiler support</a></li>
      <li><a href="${prefix}OptInFeatures.html">Opt-in features</a></li>
      <li><a href="${prefix}ExtendingLimits.html">Extending limits</a></li>
      <li><a href="${prefix}Performance.html">Performance</a></li>
    </ul>
  </li>

  <li class="even">
    <a id="CompileTimeDemos"></a>
    <strong>Compile-time demos</strong>
    <ul>
      $demo_toc
    </ul>
  </li>
</ul>

<div class="hack"></div>

%% title = Clean reflective enums for C++

%% description = Reflective enums for C++ with clean syntax, in a header-only
library. Can be converted to strings, iterated, counted, and used for
metaprogramming. Free under the BSD license.

%% class = index
