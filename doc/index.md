<div class="splash">
  <pre class="left">enable

declare


parse
format


count
iterate




switch






safe cast


during
compilation
</pre>
  <pre class="right"><em>#include &lt;enum.h&gt;</em>

<em>BETTER_ENUM(Channel, int, Red = 1, Green, Blue)</em>


Channel     c = <em>Channel::_from_string("Red")</em>;
const char  *s = <em>c._to_string()</em>;


size_t      n = <em>Channel::_size()</em>;
<em>for (Channel c : Channel::_values())</em> {
    run_some_function(c);
}


<em>switch (c)</em> {
    <em>case Channel::Red</em>:    // ...
    <em>case Channel::Green</em>:  // ...
    <em>case Channel::Blue</em>:   // ...
}


Channel     c = <em>Channel::_from_integral(3)</em>;


<em>constexpr</em> Channel c =
    <em>Channel::_from_string("Blue")</em>;</pre>
</div>

<p class="splash-text">
  $be is a single, lightweight header file that makes your compiler generate
  <em>reflective</em> enum types.
</p>

That means you can easily convert enums to and from strings,
validate them, and loop over them. In $cxx11, you can do it all at
compile time.

It's what built-in enums ought to support. Better Enums simply adds the missing
features. And, it is based on the best known techniques, thoroughly tested,
fast, portable, and documented exhaustively.

To use it, just include <code>enum.h</code> and begin the
[tutorial](${prefix}tutorial/HelloWorld.html)!

<div class="hack"></div>

### Highlights

<ul class="blurbs">
  <li class="zero-mod-two zero-mod-three">
    <strong>Unobtrusive syntax</strong>
    <em>
      No ugly macros. Use initializers as with built-in <code>enums</code>.
      Internal members have underscores to avoid clashing with your constant
      names.
    </em>
  </li>

  <li class="one-mod-two one-mod-three">
    <strong>No external dependencies</strong>
    <em>
      Uses only standard $cxx. Installation is simple &mdash; just download
      <code>enum.h</code>. There are no objects or libraries to link with.
    </em>
  </li>

  <li class="zero-mod-two two-mod-three">
    <strong>No generator program needed</strong>
    <em>
      Just include <code>enum.h</code>. It's a metaprogram executed by your
      compiler.
    </em>
  </li>

  <li class="one-mod-two zero-mod-three">
    <strong>Plays nice with <code>switch</code></strong>
    <em>
      Use a Better Enum like a built-in <code>enum</code>, and still have the
      compiler do case checking.
    </em>
  </li>

  <li class="zero-mod-two one-mod-three">
    <strong>Don't repeat yourself</strong>
    <em>
      No more unmaintanable maps or <code>switch</code> statements for
      converting enums to strings.
    </em>
  </li>

  <li class="one-mod-two two-mod-three">
    <strong>Non-contiguous sequences</strong>
    <em>
      Iteration and counting are much easier to maintain than with an extra
      <code>Count</code> constant and assuming a dense range.
    </em>
  </li>

  <li class="zero-mod-two zero-mod-three">
    <strong>Fast compilation</strong>
    <em>
      Much less impact on build time than even just including
      <code>iostream</code>. <code>enum.h</code> is only slightly more than 1000
      lines long.
    </em>
  </li>

  <li class="one-mod-two one-mod-three">
    <strong>Compile-time reflection</strong>
    <em>
      Have the compiler do additional enum processing using your own
      templates or <code>constexpr</code> functions.
    </em>
  </li>

  <li class="zero-mod-two two-mod-three">
    <strong>Uniform interface for $cxx98, $cxx11</strong>
    <em>
      Scoped, sized, reflective enums for $cxx98, and an easy upgrade
      path.
    </em>
  </li>

  <li class="one-mod-two zero-mod-three">
    <strong>Stream operators</strong>
    <em>
      Write enum names directly to <code>std::cout</code> or use
      <code>boost::lexical_cast</code>.
    </em>
  </li>

  <li class="zero-mod-two one-mod-three">
    <strong>Free and open source</strong>
    <em>
      Released under the BSD license for use in any project, free or commercial.
    </em>
  </li>
</ul>

<div class="hack"></div>

### Documentation

<ul class="blurbs resources">
  <li class="zero-mod-two zero-mod-three">
    <a id="Tutorial"></a>
    <strong>Tutorial</strong>
    <ol>
      $tutorial_toc
    </ol>
  </li>

  <li class="one-mod-two one-mod-three">
    <strong>Reference</strong>
    <ul>
      <li><a href="${prefix}ApiReference.html">API reference</a></li>
      <li><a href="${prefix}CompilerSupport.html">Compiler support</a></li>
      <li><a href="${prefix}OptInFeatures.html">Opt-in features</a></li>
      <li><a href="${prefix}ExtendingLimits.html">Extending limits</a></li>
      <li><a href="${prefix}Performance.html">Performance</a></li>
      <li>
        <a href="${prefix}DesignDecisionsFAQ.html">Design decisions FAQ</a>
      </li>
      <li>
        <a href="http://www.codeproject.com/Articles/1002895/Clean-Reflective-Enums-Enum-to-String-with-Nice-Sy">
          Implementation <span class="external">[CodeProject]</span>
        </a>
      </li>
    </ul>
  </li>

  <li class="zero-mod-two two-mod-three">
    <a id="CompileTimeDemos"></a>
    <strong>Advanced</strong>
    <ul>
      $demo_toc
    </ul>
  </li>
</ul>

<div class="hack"></div>

%% title = Clean reflective enums for C++

%% description = Reflective enums in a single header file, with clean syntax.
The enums can be converted to string, iterated, and counted, at run time or
as part of metaprogramming. Free and open source under the BSD license.

%% class = index
