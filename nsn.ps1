# NSN Interpreter in PowerShell
param([string]$ScriptFile)

Write-Host "NSN (Network Security Navigator) - PowerShell Interpreter" -ForegroundColor Cyan
Write-Host "---------------------------------------------------------"

if (-not $ScriptFile) {
    Write-Host "Usage: .\nsn.ps1 <file.nsn>" -ForegroundColor Yellow
    exit
}

if (-not (Test-Path $ScriptFile)) {
    Write-Host "Error: File '$ScriptFile' not found!" -ForegroundColor Red
    exit
}

$lines = Get-Content $ScriptFile

foreach ($line in $lines) {
    $line = $line.Trim()
    
    # Skip comments
    if ($line.StartsWith("#") -or [string]::IsNullOrWhiteSpace($line)) { continue }
    
    # print
    if ($line.StartsWith("print ")) {
        $text = $line.Substring(6).Trim('"')
        Write-Host $text
    }
    # ping
    elseif ($line.StartsWith("ping ")) {
        $target = $line.Substring(5).Trim()
        Write-Host "Pinging $target..." -ForegroundColor Gray
        ping.exe -n 2 $target | Select-Object -Skip 2 | Select-Object -First 3
    }
    # resolve
    elseif ($line.StartsWith("resolve ")) {
        $hostname = $line.Substring(8).Trim()
        Write-Host "Resolving $hostname..." -ForegroundColor Gray
        try {
            $ip = [System.Net.Dns]::GetHostAddresses($hostname)
            Write-Host "$hostname -> $($ip[0].IPAddressToString)" -ForegroundColor Green
        } catch {
            Write-Host "Failed to resolve $hostname" -ForegroundColor Red
        }
    }
    # scan
    elseif ($line.StartsWith("scan ")) {
        $args = $line.Substring(5).Trim()
        try {
            $parts = $args.Split(":")
            $ip = $parts[0]
            $port = [int]$parts[1]
            
            Write-Host "Scanning $ip port $port..." -ForegroundColor Gray
            
            $socket = New-Object System.Net.Sockets.TcpClient
            try {
                $connect = $socket.ConnectAsync($ip, $port)
                if ($connect.Wait(1000)) {
                   Write-Host "Port $port is OPEN" -ForegroundColor Green
                } else {
                   Write-Host "Port $port is CLOSED" -ForegroundColor Red
                }
            } catch {
                Write-Host "Port $port is CLOSED" -ForegroundColor Red
            } finally {
                $socket.Close()
            }
        } catch {
            Write-Host "Error scanning $args" -ForegroundColor Red
        }
    }
}
Write-Host "`nDone." -ForegroundColor Cyan
