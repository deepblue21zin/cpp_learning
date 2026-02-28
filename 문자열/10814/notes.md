# BOJ 10814 - 나이순 정렬

## REQ
- (1) 나이 오름차순 정렬
- (2) 나이가 같으면 입력(가입) 순서 유지
- 출력: 모든 회원을 정렬된 순서로 출력 (중복 제거 요구 없음)

## DS
- vector<Person> (age, name)

## Algo
- stable_sort를 사용해 "나이만" 비교한다
  - stable_sort가 같은 나이의 상대 순서를 입력 순서대로 유지해줌

## Complexity
- Time: O(N log N)
- Mem: O(N)

## cmp(Custom Comparator)
- age만 비교: a.age < b.age

## 제출 전 체크(30초)
- stable_sort 사용했는가? (sort면 순서 깨질 수 있음)
- cmp에서 <= 같은 비교를 쓰지 않았는가?
- 출력 포맷: "age name" + '\n'

## Postmortem(틀렸을 때만)
- 증상:
- 원인 1줄:
- 수정:
- 재발 방지: