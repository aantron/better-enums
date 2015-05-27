Have you noticed the awkward situation with enums in $cxx? They are missing
basic reflective features, such as string conversions. You are forced to put
them through big `switch` statements and write duplicate enum names. It's a
maintenance nightmare.

$be is a short header file that gives you rich, reflective enums, with the
nicest syntax yet seen. Just include it, and you are ready to go. You get
scoped, sized, printable, iterable enums that support initializers and still
play nice with `switch` case checking!

<div class="panes">
  <div class="pane left">
    <h3>$cxx11</h3>

    <pre>#include &lt;iostream&gt;
<em>#include &lt;enum.h&gt;</em>

<em>ENUM(Channel, int,
     Red = 1, Green, Blue)</em>

int main()
{
  <em>Channel c = Channel::Red</em>;
  std::cout &lt;&lt; <em>c._to_string()</em>;

  <em>for (Channel c : Channel::_values())</em>
    std::cout &lt;&lt; <em>c._to_string()</em>;

  <em>switch (c)</em> {
    <em>case Channel::Red</em>:
      return <em>c._to_integral()</em>;
    <em>case Channel::Green</em>: return 15;
    <em>case Channel::Blue</em>:  return 42;
  }
}

<em>constexpr</em> Channel c =
  <em>Channel::_from_string("Blue")</em>;</pre>
  </div>
  <div class="pane right">
    <h3>$cxx98</h3>
    <pre>#include &lt;iostream&gt;
<em>#include &lt;enum.h&gt;</em>

<em>ENUM(Channel, int,
     Red = 1, Green, Blue)</em>

int main()
{
  <em>Channel c = Channel::Red</em>;
  std::cout &lt;&lt; <em>c._to_string()</em>;

  for (size_t i = 0;
       <em>i < Channel::_size</em>; ++i) {

    c = <em>Channel::_values()[i]</em>;
    std::cout &lt;&lt; <em>c._to_string()</em>;
  }

  <em>switch (c)</em> {
    <em>case Channel::Red</em>:
      return <em>c._to_integral()</em>;
    <em>case Channel::Green</em>: return 15;
    <em>case Channel::Blue</em>:  return 42;
  }
}</pre>
  </div>

  <div class="hack"></div>
</div>

To install, simply <a $download>download enum.h</a> and add it to your project.

That's all. The library is header-only and has no dependencies. It is published
under the BSD license, so you can do pretty much anything you want with it.

---

Better Enums is under active development and will always be supported. Follow
the project on [GitHub]($repo) for updates.

---

<div class="panes">
  <div class="pane left">
    <h3>Tutorials</h3>
    <ol>
      $tutorial_toc
    </ol>
  </div>

  <div class="pane right">
    <h3>Advanced demos</h3>
    <ul>
      $demo_toc
    </ul>
  </div>
</div>

<div class="panes">
  <div class="pane left">
    <h3>Reference</h3>
    <ul>
      <li><a href="${prefix}ApiReference.html">API reference</a></li>
      <li><a href="${prefix}OptInFeatures.html">Opt-in features</a></li>
      <li>
        <a href="${prefix}ExtendingMacroLimits.html">Extending macro limits</a>
      </li>
      <li><a href="${prefix}CompilerSupport.html">Compiler support</a></li>
      <li><a href="${prefix}performance.html">Performance</a></li>
    </ul>
  </div>
</div>

<div class="hack"></div>

<!-- Contact -->

<!-- omfg -->

<!-- Development blurb -->

<!-- Prompts and such -->

%% title = Clean reflective enums for C++
