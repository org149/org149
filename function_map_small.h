
using namespace std;


bool lookup_and_call_small( small::Data* data, string name, string value )
  {
    if (name == "set_string_field0") { 
  data->set_string_field0(value);
}
if (name == "set_string_field1") { 
  data->set_string_field1(value);
}
if (name == "set_string_field2") { 
  data->set_string_field2(value);
}
if (name == "set_string_field3") { 
  data->set_string_field3(value);
}
if (name == "set_string_field4") { 
  data->set_string_field4(value);
}
if (name == "set_int_field0") { 
  data->set_int_field0(atoi(value.c_str()));
}
if (name == "set_int_field1") { 
  data->set_int_field1(atoi(value.c_str()));
}
if (name == "set_int_field2") { 
  data->set_int_field2(atoi(value.c_str()));
}
if (name == "set_int_field3") { 
  data->set_int_field3(atoi(value.c_str()));
}
if (name == "set_int_field4") { 
  data->set_int_field4(atoi(value.c_str()));
}
    return true;
  }
