# disk-apm-disabler

## introduction

- this tool helps you disbale the APM(Advanced Power Management) function of your HDD

- you can simply add it to your starup, and relief yourself from manually disabling APM in `crystal disk info`

- currently only available on windows

## usage

for example, you can disable apm function of physical drive 0, 1 and 3 using this command:
```
apmdisable.exe 0 1 3
```

you can simply obtain the drive number from `disk management` utility provided by windows

## notice

- this program works on ATA devices only; it currently might not work on some USB drives

- nowadays, most ATA devices `should` support for `disabling APM`, as it supports ATA5/6/7/8 or ACS2/3/4/5 standards
