/*
 * Copyright 2004,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
 #include <axis2_soap_fault_sub_code.h>
 #include <axis2_soap_fault_code.h>
 #include <axis2_soap_fault_value.h>
 #include <axis2_soap_utils.h> 
 /********************** impl struct ******************************************/
 
 typedef struct axis2_soap_fault_sub_code_impl_t
 {
    axis2_soap_fault_sub_code_t fault_sub_code;
    
    axis2_om_node_t *om_ele_node;
    
    axis2_om_element_t *om_ele;
    
    axis2_soap_fault_value_t *value;
    
    axis2_soap_fault_sub_code_t *subcode;
    
    axis2_soap_fault_code_t *parent;
    
    int soap_version;    
 
}axis2_soap_fault_sub_code_impl_t;

/************************* Macro *********************************************/

#define AXIS2_INTF_TO_IMPL(subcode) \
        ((axis2_soap_fault_sub_code_impl_t*)subcode)
        
/******************** function prototypes *************************************/

axis2_status_t AXIS2_CALL
axis2_soap_fault_sub_code_free(axis2_soap_fault_sub_code_t *fault_sub_code,
                               axis2_env_t **env);
                               
axis2_status_t AXIS2_CALL
axis2_soap_fault_sub_code_set_sub_code(
                              axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env,
                              axis2_soap_fault_sub_code_t *sub_code);
                              
axis2_soap_fault_value_t* AXIS2_CALL
axis2_soap_fault_sub_code_get_value
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env);                              
axis2_status_t AXIS2_CALL
axis2_soap_fault_sub_code_set_value
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env,
                              axis2_soap_fault_value_t *fault_sub_code_val);
                         
axis2_soap_fault_sub_code_t* AXIS2_CALL
axis2_soap_fault_sub_code_get_sub_code(
                              axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env);
                              
axis2_status_t AXIS2_CALL 
axis2_soap_fault_sub_code_set_base_node
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env,
                              axis2_om_node_t *node);
    
axis2_om_node_t* AXIS2_CALL 
axis2_soap_fault_sub_code_get_base_node
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env);
                                 
int AXIS2_CALL 
axis2_soap_fault_sub_code_get_soap_version
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env);    
axis2_status_t AXIS2_CALL 
axis2_soap_fault_sub_code_set_soap_version
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env,
                              int soap_version);                              
                                

/********************** function implementations ******************************/

AXIS2_DECLARE(axis2_soap_fault_sub_code_t *)
axis2_soap_fault_sub_code_create(axis2_env_t **env)
{
    axis2_soap_fault_sub_code_impl_t *fault_subcode_impl = NULL;
    AXIS2_ENV_CHECK(env, NULL);
    fault_subcode_impl = (axis2_soap_fault_sub_code_impl_t*) AXIS2_MALLOC(
                            (*env)->allocator,
                            sizeof(axis2_soap_fault_sub_code_impl_t));
    if(!fault_subcode_impl)
    {
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    
    fault_subcode_impl->fault_sub_code.ops = NULL;
    fault_subcode_impl->om_ele = NULL;
    fault_subcode_impl->om_ele_node = NULL;
    
    fault_subcode_impl->soap_version = AXIS2_SOAP_VERSION_NOT_SET;
    fault_subcode_impl->value = NULL;
    fault_subcode_impl->subcode = NULL;
    fault_subcode_impl->parent = NULL;
    
    fault_subcode_impl->fault_sub_code.ops = 
            (axis2_soap_fault_sub_code_ops_t*)AXIS2_MALLOC((*env)->allocator,
                sizeof(axis2_soap_fault_sub_code_ops_t));
                
    if(!(fault_subcode_impl->fault_sub_code.ops))
    {
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        AXIS2_FREE((*env)->allocator, fault_subcode_impl);
        return NULL;
    }                                                                  
    
    fault_subcode_impl->fault_sub_code.ops->free_fn = 
        axis2_soap_fault_sub_code_free;
        
    fault_subcode_impl->fault_sub_code.ops->get_sub_code =
        axis2_soap_fault_sub_code_get_sub_code;
        
    fault_subcode_impl->fault_sub_code.ops->set_sub_code = 
        axis2_soap_fault_sub_code_set_sub_code;
        
    fault_subcode_impl->fault_sub_code.ops->get_value =
        axis2_soap_fault_sub_code_get_value;
        
    fault_subcode_impl->fault_sub_code.ops->set_value =
        axis2_soap_fault_sub_code_set_value;
        
    fault_subcode_impl->fault_sub_code.ops->set_base_node =
        axis2_soap_fault_sub_code_set_base_node;
        
    fault_subcode_impl->fault_sub_code.ops->get_base_node =
        axis2_soap_fault_sub_code_get_base_node;
        
    fault_subcode_impl->fault_sub_code.ops->get_soap_version =
        axis2_soap_fault_sub_code_get_soap_version;
        
    fault_subcode_impl->fault_sub_code.ops->set_soap_version =
        axis2_soap_fault_sub_code_set_soap_version;                    
                                
  return  &(fault_subcode_impl->fault_sub_code);        
}

AXIS2_DECLARE(axis2_soap_fault_sub_code_t *)
axis2_soap_fault_sub_code_create_with_parent(axis2_env_t **env,
                            axis2_soap_fault_code_t *fault_code)
{
    axis2_soap_fault_sub_code_impl_t *fault_sub_code_impl =  NULL;
    axis2_soap_fault_sub_code_t *fault_sub_code = NULL;
    axis2_om_element_t *this_ele = NULL;
    axis2_om_node_t *this_node = NULL;
    axis2_om_node_t *parent_node = NULL;
    axis2_om_element_t *parent_ele = NULL;
    
    AXIS2_ENV_CHECK(env, NULL);
    AXIS2_PARAM_CHECK((*env)->error, fault_code, NULL);

    fault_sub_code = axis2_soap_fault_sub_code_create(env);
    if(!fault_sub_code)
        return NULL;
    fault_sub_code_impl = AXIS2_INTF_TO_IMPL(fault_sub_code);
    
    fault_sub_code_impl->parent = fault_code;
    parent_node = AXIS2_SOAP_FAULT_CODE_GET_BASE_NODE(fault_code, env);
    parent_ele  = (axis2_om_element_t *)AXIS2_OM_NODE_GET_DATA_ELEMENT(
                        parent_node, env);
                        
    this_ele = axis2_om_element_create(env, 
                                    parent_node,
                                    AXIS2_SOAP12_SOAP_FAULT_SUB_CODE_LOCAL_NAME,
                                    AXIS2_OM_ELEMENT_GET_NAMESPACE(parent_ele, env),
                                    &this_node);
    fault_sub_code_impl->om_ele = this_ele;
    fault_sub_code_impl->om_ele_node = this_node;
    AXIS2_SOAP_FAULT_CODE_SET_SUB_CODE(fault_code, env, fault_sub_code);
 return &(fault_sub_code_impl->fault_sub_code);
}

axis2_status_t AXIS2_CALL
axis2_soap_fault_sub_code_free(axis2_soap_fault_sub_code_t *fault_sub_code,
                               axis2_env_t **env)
{
    axis2_soap_fault_sub_code_impl_t *fault_sub_code_impl = NULL;
    AXIS2_FUNC_PARAM_CHECK(fault_sub_code, env, AXIS2_FAILURE);
    fault_sub_code_impl = AXIS2_INTF_TO_IMPL(fault_sub_code);
    
    if(fault_sub_code_impl->value)
    {
        AXIS2_SOAP_FAULT_VALUE_FREE(fault_sub_code_impl->value, env);
        fault_sub_code_impl->value = NULL;
    }
    if(fault_sub_code_impl->subcode)
    {
        AXIS2_SOAP_FAULT_SUB_CODE_FREE(fault_sub_code_impl->subcode, env);
        fault_sub_code_impl->subcode = NULL;
    }
    if(fault_sub_code->ops)
    {
        AXIS2_FREE((*env)->allocator, fault_sub_code->ops);
        fault_sub_code->ops = NULL;
    }
    AXIS2_FREE((*env)->allocator, fault_sub_code_impl);
    fault_sub_code_impl = NULL;
    return AXIS2_SUCCESS;
}
                               
axis2_status_t AXIS2_CALL
axis2_soap_fault_sub_code_set_sub_code(
                              axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env,
                              axis2_soap_fault_sub_code_t *sub_code)
{
    axis2_soap_fault_sub_code_impl_t *fault_subcode_impl = NULL;
    axis2_om_node_t *subcode_node = NULL;
    
    AXIS2_FUNC_PARAM_CHECK(fault_sub_code, env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, sub_code, AXIS2_FAILURE);
    
    fault_subcode_impl = AXIS2_INTF_TO_IMPL(fault_sub_code);
    if(fault_subcode_impl->subcode)
    {
        subcode_node = AXIS2_SOAP_FAULT_SUB_CODE_GET_BASE_NODE(
                            fault_subcode_impl->subcode, env);
        AXIS2_SOAP_FAULT_SUB_CODE_FREE(fault_subcode_impl->subcode, env);
        AXIS2_OM_NODE_FREE_TREE(subcode_node, env);                            
        subcode_node = NULL;
        fault_subcode_impl->subcode = NULL;
    }
    
    fault_subcode_impl->subcode = sub_code;
    subcode_node = AXIS2_SOAP_FAULT_SUB_CODE_GET_BASE_NODE(
                        sub_code, env);
                        
    AXIS2_OM_NODE_ADD_CHILD(subcode_node, env, fault_subcode_impl->om_ele_node);
    
    return AXIS2_SUCCESS;            
}
                              
axis2_soap_fault_value_t* AXIS2_CALL
axis2_soap_fault_sub_code_get_value
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env)
{
    axis2_soap_fault_sub_code_impl_t *fault_subcode_impl = NULL;
    axis2_om_node_t *subcode_node = NULL;
    axis2_om_node_t *this_node = NULL;
    axis2_soap_fault_value_t* fault_value = NULL;
    
    AXIS2_FUNC_PARAM_CHECK(fault_sub_code, env, NULL);
    fault_subcode_impl = AXIS2_INTF_TO_IMPL(fault_sub_code);
    this_node = AXIS2_SOAP_FAULT_SUB_CODE_GET_BASE_NODE(fault_sub_code, env);
    
    
    if(!(fault_subcode_impl->value))
    {
        subcode_node = axis2_soap_utils_get_child_with_name(env, 
                                            this_node, 
                                            AXIS2_SOAP12_SOAP_FAULT_VALUE_LOCAL_NAME);
                                                    
        fault_value = axis2_soap_fault_value_create(env);
        AXIS2_SOAP_FAULT_VALUE_SET_BASE_NODE(fault_value, env, subcode_node);
        fault_subcode_impl->value = fault_value;
    }
    return fault_subcode_impl->value;
}                              
axis2_status_t AXIS2_CALL
axis2_soap_fault_sub_code_set_value
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env,
                              axis2_soap_fault_value_t *fault_sub_code_val)
{
    axis2_soap_fault_sub_code_impl_t *fault_subcode_impl = NULL;
    axis2_om_node_t *value_node = NULL;
    axis2_om_node_t *my_node = NULL;
    
    AXIS2_FUNC_PARAM_CHECK(fault_sub_code, env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, fault_sub_code_val, AXIS2_FAILURE);
    
    fault_subcode_impl = AXIS2_INTF_TO_IMPL(fault_sub_code);
    if(fault_subcode_impl->value)
    {
        my_node = AXIS2_SOAP_FAULT_VALUE_GET_BASE_NODE(
                            fault_subcode_impl->value, env);
        AXIS2_SOAP_FAULT_SUB_CODE_FREE(fault_subcode_impl->value, env);
        fault_subcode_impl->value = NULL;
    }
    
    value_node = AXIS2_SOAP_FAULT_VALUE_GET_BASE_NODE(
                            fault_sub_code_val, env);
    
    axis2_soap_utils_set_new_node(env, 
                    fault_subcode_impl->om_ele_node,
                    &my_node, 
                    value_node);
                    
    fault_subcode_impl->value = fault_sub_code_val;
    return AXIS2_SUCCESS;    
}
                         
axis2_soap_fault_sub_code_t* AXIS2_CALL
axis2_soap_fault_sub_code_get_sub_code(
                              axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env)
{
    axis2_soap_fault_sub_code_impl_t *fault_subcode_impl = NULL;
    axis2_om_node_t *subcode_node = NULL;
    axis2_om_node_t *this_node = NULL;
    axis2_soap_fault_sub_code_t* subcode = NULL;
    
    AXIS2_FUNC_PARAM_CHECK(fault_sub_code, env, NULL);
    fault_subcode_impl = AXIS2_INTF_TO_IMPL(fault_sub_code);
    this_node = fault_subcode_impl->om_ele_node;
    
    
    if(!(fault_subcode_impl->subcode))
    {
        subcode_node = axis2_soap_utils_get_child_with_name(env, 
                                            this_node, 
                                            AXIS2_SOAP12_SOAP_FAULT_SUB_CODE_LOCAL_NAME);
                                                    
        subcode = axis2_soap_fault_sub_code_create(env);
        AXIS2_SOAP_FAULT_SUB_CODE_SET_BASE_NODE(subcode , env, subcode_node);
        fault_subcode_impl->subcode = subcode;
    }
    return fault_subcode_impl->subcode;
}
                              
axis2_status_t AXIS2_CALL 
axis2_soap_fault_sub_code_set_base_node
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env,
                              axis2_om_node_t *node)
{
   axis2_soap_fault_sub_code_impl_t *fault_subcode_impl = NULL;
   AXIS2_FUNC_PARAM_CHECK(fault_sub_code, env, AXIS2_FAILURE);
   AXIS2_PARAM_CHECK((*env)->error, node, AXIS2_FAILURE);
   fault_subcode_impl = AXIS2_INTF_TO_IMPL(fault_sub_code);
   
   if(AXIS2_OM_NODE_GET_NODE_TYPE(node, env) != AXIS2_OM_ELEMENT)
   {
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_INVALID_BASE_TYPE, AXIS2_FAILURE);
        return AXIS2_FAILURE;
   }
   fault_subcode_impl->om_ele_node = node;
   fault_subcode_impl->om_ele = (axis2_om_element_t *)
            AXIS2_OM_NODE_GET_DATA_ELEMENT(node, env);
   return AXIS2_SUCCESS;
}
    
axis2_om_node_t* AXIS2_CALL 
axis2_soap_fault_sub_code_get_base_node
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env)
{
     AXIS2_FUNC_PARAM_CHECK(fault_sub_code, env, NULL);
     return AXIS2_INTF_TO_IMPL(fault_sub_code)->om_ele_node;
}
                                 
int AXIS2_CALL 
axis2_soap_fault_sub_code_get_soap_version
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env)
{
     AXIS2_FUNC_PARAM_CHECK(fault_sub_code, env, AXIS2_FAILURE);
     return AXIS2_INTF_TO_IMPL(fault_sub_code)->soap_version;
} 

axis2_status_t AXIS2_CALL 
axis2_soap_fault_sub_code_set_soap_version
                             (axis2_soap_fault_sub_code_t *fault_sub_code,
                              axis2_env_t **env,
                              int soap_version)
{
     AXIS2_FUNC_PARAM_CHECK(fault_sub_code, env, AXIS2_FAILURE);
     AXIS2_PARAM_CHECK((*env)->error, soap_version, AXIS2_FAILURE);
     AXIS2_INTF_TO_IMPL(fault_sub_code)->soap_version = soap_version;
     return AXIS2_SUCCESS;
}


