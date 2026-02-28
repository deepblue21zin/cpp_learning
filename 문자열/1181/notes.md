# [문제번호] 제목
# BOJ 1181 - 단어 정렬
- REQ: 길이↑, 길이 같으면 사전순↑, 중복 제거
- DS: vector<string>
- Algo: sort(cmp) 후 unique로 중복 제거
- cmp: (len, lex)
- Time: O(N log N), Mem: O(N)

## 제출 전 체크
- unique는 sort 이후
- cmp가 len->lex 순서인지
- 출력 줄바꿈 OK

## Postmortem(틀렸을 때만)
- 원인:
- 수정:
- 재발 방지:

## 반례 체크(제출 전 30초)
- 경계값:
- 동률/중복:
- 최소/최대:
- 랜덤 소형:

## 실패 원인(틀렸을 때만)
- 증상: (WA/TLE/RE)
- 원인 1줄:
- 고친 것 1줄:
- 재발 방지 규칙 1줄: