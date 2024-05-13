/*
 * Autor: Marina Kravchuk
 */

//#include "tensorflow/lite/micro/all_ops_resolver.h"

#include "tensorflow/lite/micro/kernels/micro_ops.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"


tflite::MicroOpResolver &MODEL_GetOpsResolver()
{
    static tflite::MicroMutableOpResolver<5> s_microOpResolver;
    s_microOpResolver.AddConv2D();
    s_microOpResolver.AddDepthwiseConv2D();
    s_microOpResolver.AddPad();
	s_microOpResolver.AddAdd();
	s_microOpResolver.AddSoftmax();


    return s_microOpResolver;
}
