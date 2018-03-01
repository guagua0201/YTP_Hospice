def create_trainset():
"""
���ͰV�m���X�C
:return:
"""
trainset_tf = dict()
trainset_tf[u'C63�o��|'] = (15, 25, 0, 5, 8, 3)
trainset_tf[u'BMW i8'] = (35, 40, 1, 3, 3, 2)
trainset_tf[u'�L�ѻ�'] = (5, 0, 35, 50, 0, 0)
trainset_tf[u'��H��'] = (1, 5, 32, 15, 0, 0)
trainset_tf[u'Android 5.0'] = (10, 5, 7, 0, 2, 30)
trainset_tf[u'iPhone6'] = (5, 5, 5, 15, 8, 32)

trainset_class = dict()
trainset_class[u'C63�o��|'] = 'P'
trainset_class[u'BMW i8'] = 'P'
trainset_class[u'�L�ѻ�'] = 'S'
trainset_class[u'��H��'] = 'S'
trainset_class[u'Android 5.0'] = 'T'
trainset_class[u'iPhone6'] = 'T'

return trainset_tf, trainset_class
def cosine_similarity(v1, v2):
"""
�p���ӦV�q�������ۦ��סC�Z���V��A�ۦ��׼ƭȷ|�V���C
:param v1:
:param v2:
:return:
"""
sum_xx, sum_xy, sum_yy = 0.0, 0.0, 0.0
for i in range(0, len(v1)):
    sum_xx += math.pow(v1[i], 2)
    sum_xy += v1[i] * v2[i]
    sum_yy += math.pow(v2[i], 2)

return sum_xy / math.sqrt(sum_xx * sum_yy)

def knn_classify(input_tf, trainset_tf, trainset_class, k):
"""
����kNN�����t��k
:param input_tf: ��J�V�q
:param trainset_tf: �V�m���X�V�q
:param trainset_class: �V�m���X����
:param k: ��k�ӳ̪�F�~
:return:
"""
tf_distance = dict()
# �p��C�ӰV�m���X�S�x����r�r���W�v�V�q�M��J�V�q���Z��

print '(1) �p��V�q�Z��'
for place in trainset_tf.keys():
    tf_distance[place] = cosine_similarity(trainset_tf.get(place), input_tf)
    print '\tTF(%s) = %f' % (place, tf_distance.get(place))

# ��Z���ƧǡA���Xk�ӳ̪�Z��������

class_count = dict()
print '(2) ��K�ӳ̪�F�~������, k = %d' % k
for i, place in enumerate(sorted(tf_distance, key=tf_distance.get, reverse=True)):
    current_class = trainset_class.get(place)
    print '\tTF(%s) = %f, class = %s' % (place, tf_distance.get(place), current_class)
    class_count[current_class] = class_count.get(current_class, 0) + 1
    if (i + 1) >= k:
        break

print '(3) K�ӳ̪�F�~�����X�{�W�v�̰���������@�̫����'
input_class = ''
for i, c in enumerate(sorted(class_count, key=class_count.get, reverse=True)):
    if i == 0:
        input_class = c
    print '\t%s, %d' % (c, class_count.get(c))
print '(4) �������G = %s' % input_class

if __name__ == '__main__':
    input_tf = (10, 2, 50, 56, 8, 5)
    trainset_tf, trainset_class = create_trainset()
    knn_classify(input_tf, trainset_tf, trainset_class, k=3)