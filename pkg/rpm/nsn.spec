Name:           nsn
Version:        1.0.0
Release:        1%{?dist}
Summary:        Network Security Navigator programming language

License:        MIT
URL:            https://github.com/luaapy/Network-Security-Navigator
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc, autoconf, automake, libtool, libpcap-devel, openssl-devel, libssh-devel
Requires:       libpcap, openssl, libssh

%description
NSN is a specialized lightweight language for network analysis, 
security auditing, and network automation.

%prep
%setup -q

%build
./configure --prefix=/usr
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%files
%{_bindir}/nsn
%{_libdir}/nsn/*
%{_includedir}/nsn/*

%changelog
* Mon Jan 05 2026 Nosan- 1.0.0-1
- Initial package release
