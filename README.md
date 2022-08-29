# hangultaja

CLI 기반 한글타자 긴글연습 프로그램입니다.

## Dependencies

|라이브러리|설명|
|-|-|
|`libhangul`|한글 입력을 구현합니다.|
|`ncurses`|화면 입·출력을 구현합니다.|

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
./hangultaja $FILEPATH $LAYOUT
```

|요소|설명|
|-|-|
|`FILEPATH`|긴 글이 들어간 텍스트 파일|
|`LAYOUT`|키보드 레이아웃 선택|

### Layouts

|옵션|설명|
|-|-|
|`2`|두벌식 (기본)|
|`2y`|두벌식 옛한글|
|`3f`|세벌식 최종|
|`39`|세벌식 390|
|`3s`|세벌식 Shift 없음|
|`3y`|세벌식 옛한글|
|`32`|세벌식 두벌|
|`ro`|로마자

## Controls

|키|설명|
|-|-|
|`Enter`|다음 줄|
|`End`|프로그램 종료|

## Todo

- [ ] 타수 측정, 표시
- [x] 키보드 레이아웃 설정