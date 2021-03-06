#include "internal/ant_ml_native_internal.h"
#include "../../common/native/ant_common.h"

#include "iotjs_def.h"
#include "iotjs_uv_request.h"
#include "modules/iotjs_module_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

JS_FUNCTION(ant_ml_getMaxOfBuffer) {
  jerry_value_t argBuffer;
  iotjs_string_t argType;

  const char *type;
  iotjs_bufferwrap_t *buffer_wrap;
  size_t buffer_len;

  DJS_CHECK_ARGS(2, object, string);
  argBuffer = JS_GET_ARG(0, object);
  argType = JS_GET_ARG(1, string);

  type = iotjs_string_data(&argType);
  buffer_wrap = iotjs_jbuffer_get_bufferwrap_ptr(argBuffer);
  if (buffer_wrap == NULL) {
    return JS_CREATE_ERROR(TYPE, "Invalid buffer given");
  }
  buffer_len = iotjs_bufferwrap_length(buffer_wrap);

  if (buffer_len <= 0) {
    fprintf(stderr, "Invalid buffer length!: %d\n", buffer_len);
    iotjs_string_destroy(&argType);
    return jerry_create_undefined();
  }

  if (strncmp(type, "uint8", strlen("uint8")) == 0) {
    unsigned char *data_array = (unsigned char *)buffer_wrap->buffer;
    size_t data_len = buffer_len / sizeof(unsigned char);
    int result_max_index;
    unsigned char result_value;
    jerry_value_t ret;

    ant_ml_getMaxOfBuffer_internal_uint8(data_array, data_len,
                                         &result_max_index, &result_value);

    ret = jerry_create_object();
    iotjs_jval_set_property_jval(ret, "max_value",
                                 jerry_create_number(result_value));
    iotjs_jval_set_property_jval(ret, "max_index",
                                 jerry_create_number(result_max_index));
    iotjs_string_destroy(&argType);
    return ret;
  } else if (strncmp(type, "int32", strlen("int32")) == 0) {
    long *data_array = (long *)buffer_wrap->buffer;
    size_t data_len = buffer_len / sizeof(long);
    int result_max_index;
    long result_value;
    jerry_value_t ret;

    ant_ml_getMaxOfBuffer_internal_int32(data_array, data_len,
                                         &result_max_index, &result_value);

    ret = jerry_create_object();
    iotjs_jval_set_property_jval(ret, "max_value",
                                 jerry_create_number(result_value));
    iotjs_jval_set_property_jval(ret, "max_index",
                                 jerry_create_number(result_max_index));
    iotjs_string_destroy(&argType);
    return ret;
  } else if (strncmp(type, "float32", strlen("float32")) == 0) {
    float *data_array = (float *)buffer_wrap->buffer;
    size_t data_len = buffer_len / sizeof(float);
    int result_max_index;
    float result_value;
    jerry_value_t ret;

    ant_ml_getMaxOfBuffer_internal_float32(data_array, data_len,
                                           &result_max_index, &result_value);

    ret = jerry_create_object();
    iotjs_jval_set_property_jval(ret, "max_value",
                                 jerry_create_number(result_value));
    iotjs_jval_set_property_jval(ret, "max_index",
                                 jerry_create_number(result_max_index));
    iotjs_string_destroy(&argType);
    return ret;
  } else {
    fprintf(stderr, "Invalid type for getMaxOfBuffer!: %s\n", type);
    fprintf(stderr, "  - Valid types: uint8, int32, float32\n");
    iotjs_string_destroy(&argType);
    return jerry_create_undefined();
  }
}

jerry_value_t InitANTMLNative() {
  jerry_value_t antMLNative = jerry_create_object();
  REGISTER_ANT_API (antMLNative, ml, getMaxOfBuffer);

  initANTML();

  return antMLNative;
}