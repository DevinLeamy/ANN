import gzip, os
import numpy as np

file_path = "./res/train_labels.gz"

file_pointer = os.path.join("", file_path)

with open(file_pointer, "rb") as file:
  data = file.read()

res = np.frombuffer(gzip.decompress(data), dtype=np.uint8).copy()
print(res[:20])
# cnt = 0
# i = 0
# while cnt < 100:
#   if res[i] != 0:
#     print(i, res[i])
#     cnt += 1
#   i += 1
# print(res.shape)
# res = res[16:]
# print(res.shape)
# res = res.reshape((-1, 28 * 28))
# print(res.shape)