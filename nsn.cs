using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Diagnostics;
using System.Threading;

class NSN {
    static void Main(string[] args) {
        Console.WriteLine("NSN (Network Security Navigator) v1.0.0");
        
        if (args.Length == 0) {
            Console.WriteLine("Usage: nsn <script.nsn>");
            return;
        }

        string filename = args[0];
        if (!File.Exists(filename)) {
            Console.WriteLine("Error: File not found: " + filename);
            return;
        }

        string[] lines = File.ReadAllLines(filename);
        foreach (string rawLine in lines) {
            string line = rawLine.Trim();
            if (line.Length == 0 || line.StartsWith("#")) continue;

            if (line.StartsWith("print ")) {
                string text = line.Substring(6).Trim('"');
                Console.WriteLine(text);
            }
            else if (line.StartsWith("ping ")) {
                string target = line.Substring(5).Trim();
                Console.WriteLine("Pinging " + target + "...");
                try {
                    Process p = new Process();
                    p.StartInfo.FileName = "ping.exe";
                    p.StartInfo.Arguments = "-n 2 " + target;
                    p.StartInfo.UseShellExecute = false;
                    p.StartInfo.RedirectStandardOutput = true;
                    p.Start();
                    Console.WriteLine(p.StandardOutput.ReadToEnd());
                    p.WaitForExit();
                } catch {
                    Console.WriteLine("Ping failed to run.");
                }
            }
            else if (line.StartsWith("resolve ")) {
                string host = line.Substring(8).Trim();
                Console.Write("Resolving " + host + "... ");
                try {
                    IPAddress[] ips = Dns.GetHostAddresses(host);
                    Console.WriteLine(ips[0].ToString());
                } catch {
                    Console.WriteLine("Failed");
                }
            }
            else if (line.StartsWith("scan ")) {
                try {
                    string arg = line.Substring(5).Trim();
                    string[] parts = arg.Split(':');
                    string ip = parts[0];
                    int port = int.Parse(parts[1]);
                    
                    Console.Write("Scanning " + ip + ":" + port + "... ");
                    using (TcpClient client = new TcpClient()) {
                        var result = client.BeginConnect(ip, port, null, null);
                        var success = result.AsyncWaitHandle.WaitOne(TimeSpan.FromSeconds(1));
                        if (success && client.Connected) {
                            Console.WriteLine("OPEN");
                        } else {
                            Console.WriteLine("CLOSED");
                        }
                    }
                } catch {
                    Console.WriteLine("Error");
                }
            }
        }
    }
}
