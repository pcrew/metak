Metak
#####

Small header-only constexpr library containing a set of tools for working with variadic templates.

Provides:

- mutable ``constexpr`` - version of ``std::array`` (a.k.a ``metak::c_values_t``)
- mutable ``constexpr`` - version of ``std::string`` (a.k.a ``metak::c_strings_t``)
- saturation type conversion (a.k.a ``metak::saturate_cast``)

``metak::c_values_t`` and ``metak::c_string_t`` provides 0 const initialization.

Installation
------------

Just copy the ``include/metak`` directory to your project directory and indicate the ``-I`` flag.
If you're using an rpm_based distribution, use the ``make rpm``. As a result in the ``build/rpm`` directory you'll find the rpm package for your platform.

Requirements
------------

A C++ compiler that supports c++17. For example, I use gcc-9 and ``-std=gnu++17`` flag.

Usage
-----
see ``examples`` directory.


