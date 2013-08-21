{-# LANGUAGE BangPatterns #-}
{-# LANGUAGE ForeignFunctionInterface #-}
{-# LANGUAGE NamedFieldPuns #-}
#include <bindings.dsl.h>

module Bindings.XPathParsers
  ( c'htmlGetText
  , c'htmlEvalXPath
  , c'htmlEvalXPathContents
  , c'htmlEvalXPathRemove
  ) where

import Foreign.C.String (CString)
import Foreign.C.Types
import Foreign.Ptr (FunPtr, Ptr)

#include "parse.h"
#include "eval.h"

#ccall htmlGetText , CString -> CString -> CSize -> Ptr CString -> Ptr CSize -> IO CInt

#ccall htmlEvalXPath , CString -> CString -> CString -> CSize -> Ptr CString -> Ptr CSize -> IO CInt

#ccall htmlEvalXPathContents , CString -> CString -> CString -> CSize -> Ptr CString -> Ptr CSize -> IO CInt

#ccall htmlEvalXPathRemove , CString -> CString -> CString -> CSize -> Ptr CString -> Ptr CSize -> IO CInt
