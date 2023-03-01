%global debug_package %{nil}

Name:		%{package}
Version:	%{version}
Release:	0
Summary:	A small set of c++ meta tools.
Group:		Development/Libraries
License:	BSD
URL:		https://github.com/pcrew/%{package}
Source:		%{package}-%{version}.tar
Packager:	pcrew
BuildRoot:	/usr/

%description
A small set of c++17 meta-tools containing tricks with a variadic template.

%prep
%setup -q -n %{name}-%{version}

%install
mkdir -p %{buildroot}/usr/
mkdir -p %{buildroot}/usr/include
mkdir -p %{buildroot}/usr/include/%{package}
cp -r include/%{package}/* %{buildroot}/usr/include/%{package}/

%files
/usr/include/%{package}/*
