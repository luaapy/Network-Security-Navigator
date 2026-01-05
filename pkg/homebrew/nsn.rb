class Nsn < Formula
  desc "Network Security Navigator - A lightweight networking language"
  homepage "https://github.com/luaapy/Network-Security-Navigator"
  url "https://github.com/luaapy/Network-Security-Navigator/archive/v1.0.0.tar.gz"
  sha256 "..."

  depends_on "libpcap"
  depends_on "openssl"
  depends_on "libssh"

  def install
    system "./configure", "--prefix=#{prefix}"
    system "make"
    system "make", "install"
  end

  test do
    system "#{bin}/nsn", "--version"
  end
end
