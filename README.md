# hangultaja

CLI 기반 한글타자 긴글연습 프로그램입니다.

## Dependencies

`libhangul`: 한글 입력을 구현합니다.  
`ncurses`: 화면 입·출력을 구현합니다.

## Build

Unix, \*nix:
```sh
mkdir build
cd build
cmake ..
make
```

## Usage

```sh
./hangultaja $FILEPATH
```
`FILEPATH`: 긴 글이 들어간 텍스트 파일

## Controls

`Enter`: 다음 줄  
`End`: 프로그램 종료

## Todo

- [ ] 타수 측정, 표시
- [ ] 키보드 레이아웃 설정