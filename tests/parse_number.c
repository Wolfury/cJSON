/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unity/examples/unity_config.h"
#include "unity/src/unity.h"
#include "../cJSON.c"

static cJSON item[1];

static void assert_is_number(cJSON *number_item)
{
    TEST_ASSERT_NOT_NULL_MESSAGE(number_item, "Item is NULL.");

    TEST_ASSERT_NULL_MESSAGE(number_item->next, "Linked list next pointer is not NULL.");
    TEST_ASSERT_NULL_MESSAGE(number_item->prev, "Linked list previous pointer is not NULL");
    TEST_ASSERT_NULL_MESSAGE(number_item->child, "Child pointer is not NULL.");
    TEST_ASSERT_BITS_MESSAGE(0xFF, cJSON_Number, number_item->type, "Message type is not number.");
    TEST_ASSERT_BITS_MESSAGE(cJSON_IsReference, 0, number_item->type, "Item should not have a string as reference.");
    TEST_ASSERT_BITS_MESSAGE(cJSON_StringIsConst, 0, number_item->type, "Item should not have a const string.");
    TEST_ASSERT_NULL_MESSAGE(number_item->string, "string is not NULL.");
    TEST_ASSERT_NULL_MESSAGE(number_item->name, "Name is not NULL.");
}

static void assert_parse_number(const char *string, double real)
{
    TEST_ASSERT_NOT_NULL(parse_number(item, (const unsigned char*)string));
    assert_is_number(item);
    TEST_ASSERT_EQUAL_DOUBLE(real, item->valuedouble);
}

static void parse_number_should_parse_zero(void)
{
    assert_parse_number("0", 0);
    assert_parse_number("0.0", 0.0);
    assert_parse_number("-0", -0.0);
}

static void parse_number_should_parse_negative_integers(void)
{
    assert_parse_number("-1", -1);
    assert_parse_number("-32768", -32768.0);
    assert_parse_number("-2147483648", -2147483648.0);
}

static void parse_number_should_parse_positive_integers(void)
{
    assert_parse_number("1", 1);
    assert_parse_number("32767", 32767.0);
    assert_parse_number("2147483647", 2147483647.0);
}

static void parse_number_should_parse_positive_reals(void)
{
    assert_parse_number("0.001", 0.001);
    assert_parse_number("10e-10", 10e-10);
    assert_parse_number("10E-10", 10e-10);
    assert_parse_number("10e10", 10e10);
    assert_parse_number("123e+127", 123e127);
    assert_parse_number("123e-128", 123e-128);
}

static void parse_number_should_parse_negative_reals(void)
{
    assert_parse_number("-0.001", -0.001);
    assert_parse_number("-10e-10", -10e-10);
    assert_parse_number("-10E-10", -10e-10);
    assert_parse_number("-10e20", -10e20);
    assert_parse_number("-123e+127", -123e127);
    assert_parse_number("-123e-128", -123e-128);
}

int main(void)
{
    /* initialize cJSON item */
    memset(item, 0, sizeof(cJSON));
    UNITY_BEGIN();
    RUN_TEST(parse_number_should_parse_zero);
    RUN_TEST(parse_number_should_parse_negative_integers);
    RUN_TEST(parse_number_should_parse_positive_integers);
    RUN_TEST(parse_number_should_parse_positive_reals);
    RUN_TEST(parse_number_should_parse_negative_reals);
    return UNITY_END();
}
