// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#include <gtest/gtest.h>
#include <picosha2.h>

#include <cstddef>
#include <hash_finder_lib/report_generator.hpp>
#include <sstream>

namespace hash_finder_lib::report_generator {

    static void assert_generated_report_equals(::std::vector<::hash_finder_lib::worker::Result> const& results,
                                               ::std::string const& expected) {
        ::std::ostringstream out;
        generate_report(out, results);

        ASSERT_EQ(expected, out.str());
    }

    TEST(ReportGenerator, generate_report__empty) { assert_generated_report_equals({}, "[]"); }

    TEST(ReportGenerator, generate_report__1_entry) {
        ::std::vector<::std::uint8_t> const data = {1, 45, 51, 35, 31, 4, 7, 24, 7, 74, 27, 7, 74, 7, 24};
        ::std::vector<::std::uint8_t> hash;
        hash.resize(::picosha2::k_digest_size);
        ::picosha2::hash256(data, hash);

        assert_generated_report_equals(
            {::hash_finder_lib::worker::Result{data, hash, ::std::chrono::seconds{1604855407}}},
            "[\n"
            "  {\n"
            "    \"timestamp\": 1604855407,\n"
            "    \"hash\": \"" + ::picosha2::bytes_to_hex_string(hash)+ "\",\n"
            "    \"data\": \"" + ::picosha2::bytes_to_hex_string(data)+ "\"\n"
            "  }\n"
            "]");
    }

    TEST(ReportGenerator, generate_report__2_entries) {
        ::std::vector<::std::uint8_t> const data1 = {34, 63, 47, 33, 43, 42, 3, 42, 34, 32, 4, 26};
        ::std::vector<::std::uint8_t> hash1;
        hash1.resize(::picosha2::k_digest_size);
        ::picosha2::hash256(data1, hash1);
        ::std::vector<::std::uint8_t> const data2 = {25, 57, 83, 23, 11, 87, 12, 12, 54};
        ::std::vector<::std::uint8_t> hash2;
        hash2.resize(::picosha2::k_digest_size);
        ::picosha2::hash256(data2, hash2);

        assert_generated_report_equals(
            {
                ::hash_finder_lib::worker::Result{data1, hash1, ::std::chrono::seconds{15981289724}},
                ::hash_finder_lib::worker::Result{data2, hash2, ::std::chrono::seconds{18567961926}}
            },
            "[\n"
            "  {\n"
            "    \"timestamp\": 15981289724,\n"
            "    \"hash\": \"" + ::picosha2::bytes_to_hex_string(hash1)+ "\",\n"
            "    \"data\": \"" + ::picosha2::bytes_to_hex_string(data1)+ "\"\n"
            "  },\n"
            "  {\n"
            "    \"timestamp\": 18567961926,\n"
            "    \"hash\": \"" + ::picosha2::bytes_to_hex_string(hash2)+ "\",\n"
            "    \"data\": \"" + ::picosha2::bytes_to_hex_string(data2)+ "\"\n"
            "  }\n"
            "]");
    }

    TEST(ReportGenerator, generate_report__3_entries) {
        ::std::vector<::std::uint8_t> const data1 = {12, 68, 56, 9, 45, 8, 5, 98, 9, 231, 11, 111};
        ::std::vector<::std::uint8_t> hash1;
        hash1.resize(::picosha2::k_digest_size);
        ::picosha2::hash256(data1, hash1);
        ::std::vector<::std::uint8_t> const data2 = {12, 23, 67, 88, 222, 27, 120, 27, 80, 10, 18};
        ::std::vector<::std::uint8_t> hash2;
        hash2.resize(::picosha2::k_digest_size);
        ::picosha2::hash256(data2, hash2);
        ::std::vector<::std::uint8_t> const data3 = {87, 56, 46, 122, 10, 100, 29, 255, 36, 77, 1};
        ::std::vector<::std::uint8_t> hash3;
        hash3.resize(::picosha2::k_digest_size);
        ::picosha2::hash256(data3, hash3);

        assert_generated_report_equals(
            {
                ::hash_finder_lib::worker::Result{data1, hash1, ::std::chrono::seconds{1247619712}},
                ::hash_finder_lib::worker::Result{data2, hash2, ::std::chrono::seconds{1248712849}},
                ::hash_finder_lib::worker::Result{data3, hash3, ::std::chrono::seconds{2109814120}}
            },
            "[\n"
            "  {\n"
            "    \"timestamp\": 1247619712,\n"
            "    \"hash\": \"" + ::picosha2::bytes_to_hex_string(hash1)+ "\",\n"
            "    \"data\": \"" + ::picosha2::bytes_to_hex_string(data1)+ "\"\n"
            "  },\n"
            "  {\n"
            "    \"timestamp\": 1248712849,\n"
            "    \"hash\": \"" + ::picosha2::bytes_to_hex_string(hash2)+ "\",\n"
            "    \"data\": \"" + ::picosha2::bytes_to_hex_string(data2)+ "\"\n"
            "  },\n"
            "  {\n"
            "    \"timestamp\": 2109814120,\n"
            "    \"hash\": \"" + ::picosha2::bytes_to_hex_string(hash2)+ "\",\n"
            "    \"data\": \"" + ::picosha2::bytes_to_hex_string(data2)+ "\"\n"
            "  }\n"
            "]");
    }
} // namespace hash_finder_lib::report_generator
