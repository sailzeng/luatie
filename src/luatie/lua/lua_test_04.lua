-- ���ú���1
function test_error()
	
	print("test_error() called !!")
	
	test_error_1()
end

-- ���ú���2
function test_error_1()

	print("test_error_1() called !!")
	
	test_error_2()
end

-- ���ú���3��
function test_error_2()

	print("test_error_2() called !!")
	
	-- �䲻����
	test_error_3()
end