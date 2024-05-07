使用 brew 来安装烧录工具

```bash
brew install python3
pipx install stcgal

# 添加PATH路径到 .bashrc 或 .profile 或 .zshrc 中
	export PATH="$PATH:${HOME}/.local/bin"
	alias python='/opt/homebrew/bin/python3'


#验证
stcgal -V
```



使用开发版烧录

```bash
# 写入的设备是 stc89 (添加a后缀用来支持新设备)  , 设备号（/dev 目录下）， 写入的文件
stcgal  -P stc89a  -p  /dev/cu.wchusbserial1120   firmware.hex

# 当命令执行时会提示如下信息， 重启开发版即可
```

